import time
import socket
import json
import threading


class Session_server:
    def __init__(self):
        self.ip_socker = "127.0.0.1"
        self.port_socker = 8000
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_status = False  # 服务器状态

        self.link_server_Thread = threading.Thread(target=self.link_server)
        self.link_server_Thread.start()

        self.receive_server_Thread = threading.Thread(target=self.receive_server)

    def link_server(self):
        while not self.server_status:
            try:
                time.sleep(1)
                self.server_socket.connect((self.ip_socker, self.port_socker))
                self.server_status = True
                if not self.link_server_Thread.is_alive():
                    self.receive_server_Thread.start()
            except:
                self.server_status = False

    def receive_server(self):
        while self.server_status:
            try:
                receive_content_json = self.server_socket.recv(1024).decode('utf-8')  # 追加接收到的数据
                receive_content = json.loads(receive_content_json)
            except:
                self.server_status = False

    def send_server(self, genre, target, content):
        if self.server_status:
            data = {"genre": genre, "target": target, "data": content,
                    "datetime": time.strftime('%Y-%m-%d %H:%M:%S', time.localtime())}
            data_json = json.dumps(data)
            self.server_socket.send(data_json.encode("utf-8"))
