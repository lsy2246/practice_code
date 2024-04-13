from .Session_client import *
from .Database_formula import *


class Server_main(link_client, database):
    def __init__(self):
        link_client.__init__(self)
        database.__init__(self)

    def pick_data(self, data):
        account_state = None
        if data['genre'] == '登录':
            account_state = self.check_account_state(data['data']['account'], data['data']['password'])
            return account_state
        elif data['genre'] == '注册':
            account_data = self.sign_account(data['data']['account'], data['data']['password'])
            return account_data

    def alter_state(self, client_socket, state):
        for key, value in self.client_socket_dict.items():
            if value == client_socket:
                del self.client_socket_dict[key]
                break
        self.alter_state_database(client_socket, state)
