import wx
import threading


class LoginFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, id=1001, title='登录', pos=wx.DefaultPosition, size=(400, 300))

        # 创建菜单栏
        menu_bar = wx.MenuBar()

        # 登录菜单
        login_menu = wx.Menu()
        menu_bar.Append(login_menu, "登录")

        # 更多菜单
        more_menu = wx.Menu()
        self.register_id = wx.NewId()
        self.retrieve_id = wx.NewId()
        self.set_server_id = wx.NewId()
        more_menu.Append(self.register_id, "注册账号")
        more_menu.Append(self.retrieve_id, "找回密码")
        more_menu.Append(self.set_server_id, "服务器设置")
        menu_bar.Append(more_menu, "更多")

        self.SetMenuBar(menu_bar)

        # 创建状态栏
        self.status_bar = self.CreateStatusBar(4)
        self.status_bar.SetStatusText("服务器连接:", 0)
        self.status_bar.SetStatusText("状态:", 2)

        # 获取菜单点击事件
        self.Bind(wx.EVT_MENU, self.click_menu, id=self.register_id)
        self.Bind(wx.EVT_MENU, self.click_menu, id=self.retrieve_id)
        self.Bind(wx.EVT_MENU, self.click_menu, id=self.set_server_id)
        self.Bind(wx.EVT_MENU_OPEN, self.click_menu_title)

        # 创建注册面板
        self.panel = RegisterPanel(self)
        self.panel.Show()

    def click_menu_title(self, event):
        menu = event.GetMenu()
        menu_title = menu.GetTitle()
        if menu_title == "登录":
            self.panel.Destroy()
            self.panel = LoginPanel(self)
            self.panel.Show()
            self.Layout()



    # 点击菜单检测
    def click_menu(self, event):
        menu_id = event.GetId()
        if menu_id == self.register_id:
            self.panel.Destroy()
            self.panel = RegisterPanel(self)
            self.panel.Show()
            self.Layout()
        elif menu_id == self.retrieve_id:
            self.panel.Destroy()
            self.panel = LoginPanel(self)
            self.panel.Show()
            self.Layout()
        elif menu_id == self.set_server_id:
            self.panel.Destroy()
            self.panel = LoginPanel(self)
            self.panel.Show()
            self.Layout()


class LoginPanel(wx.Panel):
    def __init__(self, parent):
        super().__init__(parent)
        # 主盒子
        main_box = wx.BoxSizer(wx.VERTICAL)

        # 顶部盒子,目前只放了软件名
        top_box = wx.BoxSizer(wx.VERTICAL)  # 使用垂直盒子
        show_title = wx.StaticText(self, label='Lsy chat')
        show_title.SetFont(wx.Font(30, wx.FONTFAMILY_DEFAULT, wx.FONTSTYLE_NORMAL, wx.FONTWEIGHT_NORMAL))
        top_box.Add(show_title, 1, wx.ALIGN_CENTER_HORIZONTAL | wx.ALL, 10)
        main_box.Add(top_box, 0, wx.EXPAND)

        # 中部盒子,放账号和密码
        content_box = wx.BoxSizer(wx.VERTICAL)
        # 账号
        account_box = wx.BoxSizer(wx.HORIZONTAL)
        account_label = wx.StaticText(self, label=' 账号:')
        account_label.SetFont(wx.Font(15, wx.FONTFAMILY_DEFAULT, wx.FONTSTYLE_NORMAL, wx.FONTWEIGHT_NORMAL))
        account_box.Add(account_label, 0, wx.ALIGN_CENTER_VERTICAL)
        account_text = wx.TextCtrl(self, size=(300, 30))
        account_text.SetHint('请输入账号')
        account_box.Add(account_text, 1, wx.ALIGN_CENTER_VERTICAL)
        content_box.Add(account_box)
        # 添加空白控件来增加间距
        content_box.Add(wx.StaticText(self, label=''), 0, wx.ALL, 5)
        # 密码
        password_box = wx.BoxSizer(wx.HORIZONTAL)
        password_label = wx.StaticText(self, label=' 密码:')
        password_label.SetFont(wx.Font(15, wx.FONTFAMILY_DEFAULT, wx.FONTSTYLE_NORMAL, wx.FONTWEIGHT_NORMAL))
        password_box.Add(password_label, 0, wx.ALIGN_CENTER_VERTICAL)
        password_text = wx.TextCtrl(self, size=(300, 30))
        password_text.SetHint('请输入密码')
        password_box.Add(password_text, 1, wx.ALIGN_CENTER_VERTICAL)
        content_box.Add(password_box)
        main_box.Add(content_box, 0, wx.EXPAND)

        # 底部盒子
        bottom_box = wx.BoxSizer(wx.VERTICAL)
        # 登录按钮
        login_box = wx.BoxSizer(wx.VERTICAL)  # 使用垂直盒子布局
        login_label = wx.Button(self, size=(200, 50), label='登录')
        login_box.AddStretchSpacer()  # 添加一个可伸缩的空间，将登录按钮推到垂直中间
        login_box.Add(login_label, 0, wx.ALIGN_CENTER_HORIZONTAL)  # 将登录按钮添加到垂直盒子中
        login_box.AddStretchSpacer()  # 再次添加一个可伸缩的空间，将登录按钮推到垂直中间
        bottom_box.Add(login_box, 1, wx.ALIGN_CENTER_VERTICAL | wx.ALIGN_CENTER_HORIZONTAL)  # 将垂直盒子添加到底部盒子中，设置垂直和水平居中对齐
        main_box.Add(bottom_box, 1, wx.EXPAND)  # 将底部盒子添加到主盒子中，使其填满剩余空间

        self.SetSizer(main_box)


class RegisterPanel(wx.Panel):
    def __init__(self, parent):
        super().__init__(parent)

        main_box = wx.BoxSizer(wx.VERTICAL)
        # 内容盒子,放账号和密码
        content_box = wx.BoxSizer(wx.VERTICAL)
        # 账号
        account_box = wx.BoxSizer(wx.HORIZONTAL)
        account_label = wx.StaticText(self, label=' 账号:')
        account_label.SetFont(wx.Font(15, wx.FONTFAMILY_DEFAULT, wx.FONTSTYLE_NORMAL, wx.FONTWEIGHT_NORMAL))
        account_box.Add(account_label, 0, wx.ALIGN_CENTER_VERTICAL)
        account_text = wx.TextCtrl(self, size=(300, 30))
        account_text.SetHint('请输入账号')
        account_box.Add(account_text, 1, wx.ALIGN_CENTER_VERTICAL)
        content_box.Add(account_box)
        # 添加空白控件来增加间距
        content_box.Add(wx.StaticText(self, label=''), 0, wx.ALL, 5)
        # 密码
        password_box = wx.BoxSizer(wx.HORIZONTAL)
        password_label = wx.StaticText(self, label=' 密码:')
        password_label.SetFont(wx.Font(15, wx.FONTFAMILY_DEFAULT, wx.FONTSTYLE_NORMAL, wx.FONTWEIGHT_NORMAL))
        password_box.Add(password_label, 0, wx.ALIGN_CENTER_VERTICAL)
        password_text = wx.TextCtrl(self, size=(300, 30))
        password_text.SetHint('请输入密码')
        password_box.Add(password_text, 1, wx.ALIGN_CENTER_VERTICAL)
        content_box.Add(password_box)
        main_box.Add(content_box, 0, wx.EXPAND)

        self.SetSizer(main_box)
