import wx
from Client.Chat_main import ChatFrame

if __name__ == '__main__':
    app = wx.App()
    frame = ChatFrame()
    frame.Show()
    app.MainLoop()

