import string
import time
import socket
from threading import Thread
import random
import json


class Session_server:
    def __init__(self, ip_socker, port_socker):
        self.ip_socker = ip_socker
        self.port_socker = port_socker
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.server_status = False  # 服务器状态

    def Link_server(self):
        Verification_code = ""
        for _ in range(20):
            if random.choice([True, False]):
                Verification_code += str(random.randint(0, 9))
            else:
                Verification_code += random.choice(string.ascii_letters)
        data = {"genre": "test", "source": "Link_server", "data": Verification_code,
                "datetime": time.strftime('%Y-%m-%d %H:%M:%S', time.localtime())}
        data_json = json.dumps(data)
        self.server_socket.sendto(data_json.encode("utf-8"), (self.ip_socker, self.port_socker))
        receive_content_json = self.server_socket.recv(1024).decode('utf-8')
        receive_content = json.loads(receive_content_json)
        if receive_content["data"] == Verification_code:
            self.server_status = True  # 服务器状态
            Receive_server_Thread = Thread(target=self.Receive_server)
            Receive_server_Thread.daemon = True
            Receive_server_Thread.start()


    def Receive_server(self):
        while self.server_status:
            receive_content_json = self.server_socket.recv(1024).decode('utf-8')  # 追加接收到的数据
            receive_content = json.loads(receive_content_json)
            print(receive_content)

    def Send_server(self, genre, source, content):
        if self.server_status:
            data = {"genre": genre, "source": source, "data": content,
                    "datetime": time.strftime('%Y-%m-%d %H:%M:%S', time.localtime())}
            data_json = json.dumps(data)
            self.server_socket.sendto(data_json.encode("utf-8"), (self.ip_socker, self.port_socker))
