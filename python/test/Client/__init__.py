from .Login import *
from .Session_server import *
from .Chat_main import *


class start_all:
    def __init__(self):

        Session_server()

        app = wx.App(False)
        frame = LoginFrame()
        frame.Show(True)
        app.MainLoop()
