import wx
from Cilent import Client_main

if __name__ == '__main__':
    app = wx.App()
    frame = Client_main()
    frame.Show()
    app.MainLoop()
