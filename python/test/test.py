import string
import threading
import time
import socket
import random
import json
import concurrent.futures


class Session_server:
    def __init__(self, ip_socker, port_socker):
        self.ip_socker = ip_socker
        self.port_socker = port_socker
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.server_status = False  # 服务器状态

        # 创建线程池
        self.executor = concurrent.futures.ThreadPoolExecutor(max_workers=2)

        # 启动连接服务器的任务
        self.executor.submit(self.Link_server)

    def Link_server(self):
        while True:
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
            try:
                receive_content_json = self.server_socket.recv(1024).decode('utf-8')
                receive_content = json.loads(receive_content_json)
                if receive_content["data"] == Verification_code:
                    self.server_status = True  # 服务器状态
                    # 启动接收服务器响应的任务
                    self.executor.submit(self.Receive_server)
                else:
                    self.server_status = False
            except:
                self.server_status = False
            time.sleep(60)

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
