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
            return {"state": account_state, "user": data['data']['account']}
        elif data['genre'] == '注册':
            pass
