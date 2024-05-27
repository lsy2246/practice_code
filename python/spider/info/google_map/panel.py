import wx
import re


class reptile_Panel(wx.Frame):
    def __init__(self):
        super().__init__(None, title="谷歌地图信息提取器", size=(300, 200))

        main_panel = wx.Panel(self)
        main_box = wx.BoxSizer(wx.VERTICAL)

        # URL区域
        url_box = wx.BoxSizer(wx.HORIZONTAL)
        url_text = wx.StaticText(main_panel, label="url:")
        url_box.Add(url_text, 0, wx.ALIGN_CENTER_VERTICAL | wx.RIGHT, 5)
        self.url_input = wx.TextCtrl(main_panel)
        url_box.Add(self.url_input, 1, wx.EXPAND)
        main_box.Add(url_box, 0, wx.EXPAND | wx.ALL, 5)

        # 可视化切换
        view_box = wx.BoxSizer(wx.HORIZONTAL)
        view_text = wx.StaticText(main_panel, label="是否开启过程可视化:")
        view_box.Add(view_text, 0, wx.ALIGN_CENTER_VERTICAL | wx.RIGHT, 5)
        self.view_button_yes = wx.RadioButton(main_panel, label="是", style=wx.RB_GROUP)
        view_box.Add(self.view_button_yes, 0, wx.ALL, 5)
        self.view_button_no = wx.RadioButton(main_panel, label="否")
        view_box.Add(self.view_button_no, 0, wx.ALL, 5)
        main_box.Add(view_box, 0, wx.EXPAND | wx.ALL, 5)

        # 范围选择
        range_box = wx.BoxSizer(wx.HORIZONTAL)
        range_text = wx.StaticText(main_panel, label="商家范围(数字越大,范围越大):")
        range_box.Add(range_text, 0, wx.ALIGN_CENTER_VERTICAL | wx.RIGHT, 5)
        self.range_input = wx.SpinCtrl(main_panel, value='0', min=0, max=100)
        range_box.Add(self.range_input, 0, wx.ALIGN_CENTER_VERTICAL | wx.RIGHT, 5)
        main_box.Add(range_box, 0, wx.EXPAND | wx.ALL, 5)

        # 提交按钮
        submit_button = wx.Button(main_panel, size=(10, 40), label='提取')
        main_box.Add(submit_button, 1, wx.ALL | wx.EXPAND, 5)
        submit_button.Bind(wx.EVT_BUTTON, self.submit_function)

        # 设置主面板的布局器并显示窗口
        main_panel.SetSizer(main_box)
        self.Show()

    def submit_function(self, event):
        url = self.url_input.GetValue()
        url_pattern = re.compile(r'^https://www\.google\.com.*?&entry=ttu$')
        if not re.fullmatch(url_pattern, url):
            wx.MessageBox('url填写错误', '提示', wx.OK | wx.ICON_INFORMATION)
            return
        if self.view_button_yes.GetValue():
            head = True
        elif self.view_button_no.GetValue():
            head = False
        frequency = int(self.range_input.GetValue())
        self.submit_info(url, head, frequency)

    def submit_info(self, url, head, frequency):
        pass
