import json
import multiprocessing
from multiprocessing.connection import Listener
import threading


class ProcessServer:
    def __init__(self):
        try:
            self.Process_port = 8727
            self.Process_server = 'localhost'
            self.Process_server_listener = Listener((self.Process_server, self.Process_port))
            self.Process_client_link_dick = {}
            Process_client_link_Thread = threading.Thread(target=self.Process_client_link)
            Process_client_link_Thread.start()
        except:
            print("进程通信端口绑定失败")

    def Process_client_link(self):
        while True:
            client_connect = self.Process_server_listener.accept()
            client_Thread_recv = threading.Thread(target=self.Process_client_recv, args=(client_connect,))
            client_Thread_recv.start()

    def Process_client_recv(self, client_Thread_recv):
        while True:
            try:
                data_json = client_Thread_recv.recv()
                data = json.loads(data_json)
                if data['target'] == 'Server':
                    if data['function'] == 'Name':
                        self.Process_client_link_dick[data['content']] = client_Thread_recv
                else:
                    self.Process_client_pick(data)
            except ConnectionResetError as e:
                print("进程关闭" + str(e))

    def Process_client_send(self, target, function, content):
        connect = self.Process_client_link_dick[target]
        data = {"target": target, "function": function, "content": content}
        data_json = json.dumps(data)
        connect.send(data_json)

    def Process_client_pick(self, data):
        if data['target'] == 'ALL':
            for value in self.Process_client_link_dick.values():
                data_json = json.dumps(data)
                value.send(data_json)
        else:
            if data['target'] in self.Process_client_link_dick.keys():
                data_json = json.dumps(data)
                self.Process_client_link_dick[data['target']].send(data_json)
