import wx
from Cilent import LoginFrame
if __name__ == '__main__':
    app = wx.App()
    frame = LoginFrame()
    frame.Show()
    app.MainLoop()