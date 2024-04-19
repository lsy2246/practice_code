import wx

class ChatFrame(wx.Frame):
    def __init__(self, *args, **kwargs):
        super(ChatFrame, self).__init__(*args, **kwargs)

        self.panel = wx.Panel(self)
        self.sizer = wx.BoxSizer(wx.VERTICAL)

        self.contact_message = wx.StaticText(self.panel, label="Contact's message")
        self.my_message = wx.StaticText(self.panel, label="My message", style=wx.ALIGN_RIGHT)

        self.sizer.Add(self.contact_message, flag=wx.EXPAND|wx.LEFT, border=10)
        self.sizer.Add(self.my_message, flag=wx.EXPAND|wx.RIGHT, border=10)

        self.panel.SetSizer(self.sizer)

app = wx.App()
frame = ChatFrame(None)
frame.Show()
app.MainLoop()
