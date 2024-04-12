import time
import socket
import random
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
        if client_socket in self.client_socket_dict:
            try:
                data = {"genre": genre, "target": target, "data": content,
                        "datetime": time.strftime('%Y-%m-%d %H:%M:%S', time.localtime())}
                data_json = json.dumps(data)
                client_socket.send(data_json.encode("utf-8"))
            except Exception as a:
                print("发送错误:" + str(a))

    def pick_data(self, data):
        pass

    def recv_client(self, client_socket):
        while True:
            try:
                data_json = client_socket.recv(1024).decode('utf-8')
                data = json.loads(data_json)
                print(data_json["genre"])
                if data_json["genre"] == '登录':
                    content = self.pick_data(data)
                    print(content['state'])
                    if content['state'] == 0:
                        self.client_socket_dict[content['user']] = client_socket
                        print(self.client_socket_dict[content['user']])
                else:
                    self.pick_data(data)
            except:
                client_socket.close()
