import time
import socket
import json
import threading


class Session_server:
    def __init__(self):
        self.socker_ip = "127.0.0.1"
        self.socker_port = 8000
        self.server_socket = None
        self.server_status = False  # 服务器状态

        self.link_server_Thread = threading.Thread(target=self.link_server)
        self.link_server_Thread.start()

        self.receive_server_Thread = threading.Thread(target=self.receive_server)

    def link_server(self):
        while True:
            if not self.server_status:
                time.sleep(1)
                if self.server_socket is not None:
                    self.server_socket = None
                try:
                    self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                    self.server_socket.connect((self.socker_ip, self.socker_port))
                    self.server_status = True
                    if not self.receive_server_Thread.is_alive():
                        self.receive_server_Thread.start()
                except Exception as a:
                    self.server_status = False
                    print("连接错误:" + str(a))

    def login_page_receive(self, receive_content):
        pass

    def receive_server(self):
        while self.server_status:
            try:
                receive_content_json = self.server_socket.recv(1024).decode('utf-8')
                receive_content = json.loads(receive_content_json)
                if receive_content["genre"] in ['注册', '登录']:
                    self.login_page_receive(receive_content)
                print(receive_content)
            except Exception as a:
                print("接收错误:" + str(a))
                self.server_status = False

    def send_server(self, genre, target, content):
        if self.server_status:
            try:
                data = {"genre": genre, "target": target, "data": content,
                        "datetime": time.strftime('%Y-%m-%d %H:%M:%S', time.localtime())}
                data_json = json.dumps(data)
                self.server_socket.send(data_json.encode("utf-8"))
            except Exception as a:
                print("发送错误:" + str(a))
                self.server_status = False
