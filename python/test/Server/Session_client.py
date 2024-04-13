import time
import socket
import json
import threading


class link_client:
    def __init__(self):
        self.server_host = "127.0.0.1"
        self.server_port = 8000
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.bind((self.server_host, self.server_port))
        self.server_socket.listen()
        self.client_socket_dict = {}

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

    def pick_data(self, data):
        pass

    def recv_client(self, client_socket):
        state = True
        while state:
            try:
                data_json = client_socket.recv(1024).decode('utf-8')
                data = json.loads(data_json)
                if data["genre"] == '登录':
                    content = self.pick_data(data)
                    if data['data']['account'] not in self.client_socket_dict:
                        if content == 0:
                            self.client_socket_dict[data['data']['account']] = client_socket
                            self.alter_state(data['data']['account'], "在线")
                        self.send_client(client_socket, data["genre"], '客户端', content)
                    else:
                        self.send_client(client_socket, data["genre"], '客户端', -1)
                elif data["genre"] == '注册':
                    content = self.pick_data(data)
                    self.send_client(client_socket, data["genre"], '客户端', content)
                else:
                    self.pick_data(data)
            except:
                try:
                    client_socket.close()
                finally:
                    state = False
                    self.alter_state(client_socket, "离线")

    def alter_state(self, client_socket, state):
        pass
