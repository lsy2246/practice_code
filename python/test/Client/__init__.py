from .Page import *
from .Socket_session import *
from .Process_session import *


class start_all:
    def __init__(self):

        ProcessServer()
        Session_server()

        app = wx.App()
        frame = LoginFrame()
        frame.Show()
        app.MainLoop()
