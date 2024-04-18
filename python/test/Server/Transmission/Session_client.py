import os
import random
import string
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
        self.client_max_id = 0

        current_file_path = __file__
        current_file_name = os.path.basename(current_file_path).split('.')[0]
        self.Process_client_send("Server", "Name", current_file_name)

        self.link_client_Thread = threading.Thread(target=self.link_client)
        self.link_client_Thread.start()

    def link_client(self):
        while True:
            try:
                client_socket, client_address = self.server_socket.accept()
                self.client_max_id += 1
                client_id = ''.join(random.choice(string.ascii_letters) for _ in range(10)) + str(self.client_max_id)
                self.client_socket_dict[client_id] = client_socket
                recv_client_Thread = threading.Thread(target=self.recv_client(client_socket), daemon=True)
                recv_client_Thread.start()
            except:
                pass

    def send_client(self, client_id, genre, target, content):
        client_socket = self.client_socket_dict[client_id]
        try:
            data = {"genre": genre, "target": target, "data": content,
                    "datetime": time.strftime('%Y-%m-%d %H:%M:%S', time.localtime())}
            data_json = json.dumps(data)
            client_socket.send(data_json.encode("utf-8"))
        except:
            client_socket.close()

    def pick_data(self, client_id, data):
        match data['genre']:
            case '登录':
                content = {'client_id': client_id, 'account': data['data']['account'],
                           'password': data['data']['password']}
                self.Process_client_send("Database_formula", "check_account_state", content)
            case '注册':
                content = {'client_id': client_id, 'account': data['data']['account'],
                           'password': data['data']['password']}
                self.Process_client_send("Database_formula", "sign_account", content)
            case '数据更新':
                content = {'client_id': client_id, 'date': data['data']}
                self.Process_client_send("Database_formula", "detection_data", content)

    def recv_client(self, client_socket):
        state = True
        while state:
            try:
                data_json = client_socket.recv(1024).decode('utf-8')
                data = json.loads(data_json)
                client_Id = self.find_client(client_socket, None)
                self.pick_data(client_Id, data)
            except:
                try:
                    client_socket.close()
                finally:
                    state = False
                    self.find_client(client_socket, None)
                    client_id = self.find_client(client_socket, None)
                    del self.client_socket_dict[client_id]
                    if client_id.isdigit():
                        self.Process_client_send("Database_formula", "alter_state_database",
                                                 {"Id": client_id, "sate": 0})

    def Process_client_pick(self, data):
        if data['target'] in ['ALL', 'Session_client']:
            match data['function']:
                case 'send_client':
                    client_id = data['content']['client_id']
                    genre = data['content']['genre']
                    target = data['content']['target']
                    content = data['content']['data']
                    if data['content']['genre'] == '登录':
                        if content['account'] not in self.client_socket_dict:
                            if content['status'] == 0:
                                client_socket = self.find_client(None, client_id)
                                del self.client_socket_dict[client_id]
                                client_id = content['account']
                                self.client_socket_dict[client_id] = client_socket
                                if client_id.isdigit():
                                    self.Process_client_send("Database_formula", "alter_state_database",
                                                             {"Id": client_id, "sate": 1})
                        else:
                            return
                    self.send_client(client_id, genre, target, content)

    def find_client(self, client_socket, client_id):
        if client_id is None:
            for key, value in self.client_socket_dict.items():
                if value == client_socket:
                    return key
        elif client_socket is None:
            for key, value in self.client_socket_dict.items():
                if key == client_id:
                    return value
