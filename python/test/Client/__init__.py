from .Page import *
from .Transmission import *


class start_all:
    def __init__(self):
        ProcessServer()

        Session_server()

        FileOperate(None)

        app = wx.App()
        LoginFrame().Show()
        app.MainLoop()

