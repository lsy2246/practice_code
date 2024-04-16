import wx
from Client.Page.Chat_main import ChatFrame

if __name__ == '__main__':
    app = wx.App()
    frame = ChatFrame("lsy")
    frame.Show()
    app.MainLoop()

