import json
import threading
from multiprocessing.connection import Client


class ProcessClient:
    def __init__(self):
        self.Process_port = 8727
        self.Process_server = 'localhost'
        self.Process_client_Client = Client((self.Process_server, self.Process_port))
        Process_client_recv = threading.Thread(target=self.Process_client_recv)
        Process_client_recv.start()

    def Process_client_send(self, target, function, content):
        data = {"target": target, "function": function, "content": content}
        data_json = json.dumps(data)
        self.Process_client_Client.send(data_json)

    def Process_client_recv(self):
        while True:
            try:
                data_json = self.Process_client_Client.recv()
                data = json.loads(data_json)
                self.Process_client_pick(data)

            except ConnectionResetError as e:
                print("连接已关闭: " + str(e))
                break

    def Process_client_pick(self, data):
        pass
