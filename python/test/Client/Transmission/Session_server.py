import multiprocessing
import os
import time
import socket
import json
import threading
from .Process_Client import ProcessClient


class Session_server(ProcessClient):
    def __init__(self):
        ProcessClient.__init__(self)
        self.socker_ip = "127.0.0.1"
        self.socker_port = 7868
        self.server_socket = None
        self.server_status = False  # 服务器状态
        self.link_server_Thread = threading.Thread(target=self.link_server)
        self.link_server_Thread.start()
        self.receive_server_Thread = threading.Thread(target=self.receive_server)

        current_file_path = __file__
        current_file_name = os.path.basename(current_file_path).split('.')[0]
        self.Process_client_send("Server", "Name", current_file_name)

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
                finally:
                    self.Process_client_send("ALL", "server_status", self.server_status)
                    pass

    def receive_server(self):
        while self.server_status:
            try:
                receive_content_json = self.server_socket.recv(1024).decode('utf-8')
                receive_content = json.loads(receive_content_json)
                self.content_pick(receive_content)
            except Exception as a:
                print("客户端接收错误:" + str(a))
                self.server_status = False
                self.Process_client_send("ALL", "server_status", self.server_status)

    def send_server(self, genre, target, content):
        if self.server_status:
            try:
                data = {"genre": genre, "target": target, "data": content,
                        "datetime": time.strftime('%Y-%m-%d %H:%M:%S', time.localtime())}
                data_json = json.dumps(data)+'\n'
                self.server_socket.send(data_json.encode("utf-8"))
            except Exception as a:
                print("发送错误:" + str(a))
                self.server_status = False
                self.Process_client_send("ALL", "server_status", self.server_status)

    def Process_client_pick(self, data):
        if data['target'] in ['ALL', 'Session_server']:
            match data['function']:
                case 'server_status':
                    self.server_status = data['content']
                case 'send_server':
                    self.send_server(data['content']['genre'], data['content']['target'], data['content']['content'])

    def content_pick(self,data):
        match data['genre']:
            case '注册' | '登录':
                self.Process_client_send("Login", "login_page_receive", data)
            case '数据更新':
                self.Process_client_send("file_operate", "save_data", data['data'])


