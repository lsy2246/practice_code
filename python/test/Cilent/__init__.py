from .Login import *
from .Session_server import *


class Client_main(LoginFrame, Session_server):
    def __init__(self, ip_socker, port_socker):
        Session_server.__init__(self, ip_socker, port_socker)
        LoginFrame.__init__(self)
        Session_server.Link_server(self)

        # 主页按键绑定

    def Sign_Account(self, event):
        if self.GetParent().server_status:
            pass
