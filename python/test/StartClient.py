import wx
from Cilent import Client_main

if __name__ == '__main__':
    app = wx.App()
    frame = Client_main("127.0.0.1", 8000)  # 这里填写你的 ip_socker 和 port_socker
    frame.Show()
    app.MainLoop()
