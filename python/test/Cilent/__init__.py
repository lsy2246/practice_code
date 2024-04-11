from .Login import *
from .Session_server import *


class Client_main(LoginFrame, Session_server):
    def __init__(self):
        Session_server.__init__(self)  # 与服务器会话
        LoginFrame.__init__(self)




