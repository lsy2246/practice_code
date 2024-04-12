import wx


class MultiPanelFrame(wx.Frame):
    def __init__(self):
        super().__init__(None, title="Multi Panel Example", size=(400, 300))

        self.panel1 = wx.Panel(self)
        self.panel2 = wx.Panel(self)
        self.panel3 = wx.Panel(self)

        self.panel1.SetBackgroundColour(wx.Colour(255, 0, 0))  # Red
        self.panel2.SetBackgroundColour(wx.Colour(0, 255, 0))  # Green
        self.panel3.SetBackgroundColour(wx.Colour(0, 0, 255))  # Blue

        self.sizer = wx.BoxSizer(wx.VERTICAL)
        self.sizer.Add(self.panel1, 1, wx.EXPAND)
        self.sizer.Add(self.panel2, 1, wx.EXPAND)
        self.sizer.Add(self.panel3, 1, wx.EXPAND)

        self.panel1.Show()
        self.panel2.Hide()
        self.panel3.Hide()

        self.SetSizer(self.sizer)

        self.Bind(wx.EVT_CHAR_HOOK, self.on_key_press)

    def on_key_press(self, event):
        key = event.GetKeyCode()
        if key == ord('1'):
            self.panel1.Show()
            self.panel2.Hide()
            self.panel3.Hide()
            self.Layout()
        elif key == ord('2'):
            self.panel1.Hide()
            self.panel2.Show()
            self.panel3.Hide()
            self.Layout()
        elif key == ord('3'):
            self.panel1.Hide()
            self.panel2.Hide()
            self.panel3.Show()
            self.Layout()


if __name__ == "__main__":
    app = wx.App()
    frame = MultiPanelFrame()
    frame.Show()
    app.MainLoop()
