from .Transmission import *


class Server_main:
    def __init__(self):
        ProcessServer()
        database()
        link_client()



