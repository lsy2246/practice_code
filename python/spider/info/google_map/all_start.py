from script import *
from panel import *

class full_panel(reptile_Panel):
    def __init__(self):
        super().__init__()

    def submit_info(self, url, head, frequency):
        google_map = google_map_script(url, head, frequency)
        wx.MessageBox('开始提取', '提示', wx.OK | wx.ICON_INFORMATION)
        google_map.start()
        wx.MessageBox('提取完成', '提示', wx.OK | wx.ICON_INFORMATION)


app = wx.App()
full_panel().Show()
app.MainLoop()

