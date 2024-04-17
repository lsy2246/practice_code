import os
import time
import socket
import json
import threading
from .Process_Client import *


class link_client(ProcessClient):
    def __init__(self):
        ProcessClient.__init__(self)
        self.server_host = "127.0.0.1"
        self.server_port = 7868
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.bind((self.server_host, self.server_port))
        self.server_socket.listen()
        self.client_socket_dict = {}

        current_file_path = __file__
        current_file_name = os.path.basename(current_file_path).split('.')[0]
        self.Process_client_send("Server", "Name", current_file_name)

        self.link_client_Thread = threading.Thread(target=self.link_client)
        self.link_client_Thread.start()

    def link_client(self):
        while True:
            try:
                client_socket, client_address = self.server_socket.accept()
                recv_client_Thread = threading.Thread(target=self.recv_client(client_socket), daemon=True)
                recv_client_Thread.start()
            except:
                pass

    def send_client(self, client_socket, genre, target, content):
        try:
            data = {"genre": genre, "target": target, "data": content,
                    "datetime": time.strftime('%Y-%m-%d %H:%M:%S', time.localtime())}
            data_json = json.dumps(data)
            client_socket.send(data_json.encode("utf-8"))
        except:
            client_socket.close()

    def pick_data(self, client_socket, data):
        match data['genre']:
            case '登录':
                content = {'client_socket': client_socket, 'account': data['data']['account'],
                           'password': data['data']['password']}
                self.Process_client_send("Database_formula", "check_account_state", content)
            case '注册':
                content = {'client_socket': client_socket, 'account': data['data']['account'],
                           'password': data['data']['password']}
                self.Process_client_send("Database_formula", "sign_account", content)

    def recv_client(self, client_socket):
        state = True
        while state:
            try:
                data_json = client_socket.recv(1024).decode('utf-8')
                data = json.loads(data_json)
                self.pick_data(client_socket, data)
            except:
                try:
                    client_socket.close()
                finally:
                    state = False
                    for key, value in self.client_socket_dict.items():
                        if value == client_socket:
                            del self.client_socket_dict[key]
                            self.Process_client_send("Database_formula", "alter_state_database",
                                                     {"Id": key, "sate": "在线"})
                            break

    def Process_client_pick(self, data):
        if data['target'] in ['ALL', 'Session_client']:
            match data['function']:
                case 'send_client':
                    client_socket = data['content']['client_socket']
                    genre = data['content']['genre']
                    target = data['content']['target']
                    content = data['content']['content']
                    self.send_client(client_socket, genre, target, content)
                    if target == '登录':
                        if data['content']['status'] == 0:
                            self.client_socket_dict[data['content']['account']] = data['data']['client_socket']
                            self.Process_client_send("Database_formula", "alter_state_database",
                                                     {"Id": data['content']['account'],
                                                      "sate": "在线"})
