import wx

app = wx.App()

# 创建一个Frame
frame = wx.Frame(None, -1, '多行文本弹窗示例', size=(300, 200))
frame.Center()

# 创建一个Panel
panel = wx.Panel(frame, -1)

# 创建一个按钮
button = wx.Button(panel, -1, '点击弹窗', pos=(100, 50))

# 定义按钮的点击事件处理函数
def on_button_click(event):
    message = "这是一个多行文本的弹窗。\n第二行文本。\n第三行文本。"
    dlg = wx.MessageDialog(frame, message, '多行文本提示', wx.OK | wx.ICON_INFORMATION)
    dlg.ShowModal()
    dlg.Destroy()

# 绑定按钮的点击事件
button.Bind(wx.EVT_BUTTON, on_button_click)

frame.Show()
app.MainLoop()
