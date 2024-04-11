import string
import time
import socket
import random
import json
import threading


class link_client:
    def __init__(self ):
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
                data_json = self.server_socket.recv(1024).decode('utf-8')
                data = json.loads(data_json)
                print(data)
            except:
                print("无")
