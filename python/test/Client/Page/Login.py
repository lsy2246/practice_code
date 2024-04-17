import json
import multiprocessing
import os

import wx
import threading
import time
from Client.Transmission.Process_Client import ProcessClient
from .Chat_main import ChatFrame


def open_chat_window(Id):
    app = wx.App()
    ChatFrame(Id).Show()
    app.MainLoop()


class LoginFrame(wx.Frame, ProcessClient):
    def __init__(self):
        wx.Frame.__init__(self, None, id=-1, title='登录', pos=wx.DefaultPosition, size=(380, 300))
        ProcessClient.__init__(self)


        current_file_path = __file__
        current_file_name = os.path.basename(current_file_path).split('.')[0]
        self.Process_client_send("Server", "Name", current_file_name)

        # 创建菜单栏
        menu_bar = wx.MenuBar()

        # 登录菜单
        login_menu = wx.Menu()
        menu_bar.Append(login_menu, "登录")

        # 更多菜单
        more_menu = wx.Menu()
        self.register_id = wx.NewId()
        self.set_server_id = wx.NewId()
        more_menu.Append(self.register_id, "注册账号")
        more_menu.Append(self.set_server_id, "服务器设置")
        menu_bar.Append(more_menu, "更多")

        self.SetMenuBar(menu_bar)

        # 创建状态栏
        self.status_bar = self.CreateStatusBar(2)
        self.server_status = False  # 服务器状态
        status_thread = threading.Thread(target=self.update_status_bar(None), daemon=True)
        status_thread.start()

        # 启动定时器，每秒钟触发一次
        self.timer = wx.Timer(self)
        self.Bind(wx.EVT_TIMER, self.update_status_bar, self.timer)
        self.timer.Start(1000)  # 设置定时器间隔为1000毫秒（1秒

        # 获取菜单点击事件
        self.Bind(wx.EVT_MENU, self.click_menu, id=self.register_id)
        self.Bind(wx.EVT_MENU, self.click_menu, id=self.set_server_id)
        self.Bind(wx.EVT_MENU_OPEN, self.click_menu_title)

        # 创建注册面板
        self.sizer = wx.BoxSizer(wx.VERTICAL)
        self.login_panel = LoginPanel(self)
        self.register_panel = RegisterPanel(self)
        self.sizer.Add(self.login_panel, 1, wx.EXPAND)
        self.sizer.Add(self.register_panel, 1, wx.EXPAND)

        self.login_panel.Hide()
        self.register_panel.Hide()

        self.login_panel.Show()

        # 主页按钮绑定
        self.Bind(wx.EVT_BUTTON, self.send_login_button, self.login_panel.LoginPanel_login_label)
        self.Bind(wx.EVT_BUTTON, self.send_register_button, self.register_panel.RegisterPanel_login_label)

        self.SetSizer(self.sizer)

    def update_status_bar(self, event):
        if self.server_status:
            self.status_bar.SetStatusText("服务器\t已连接", 0)
        else:
            self.status_bar.SetStatusText("服务器\t未连接", 0)

        self.status_bar.SetStatusText("时间\t" + time.strftime('%Y-%m-%d %H:%M:%S', time.localtime()), 1)

    def click_menu_title(self, event):
        menu = event.GetMenu()
        menu_title = menu.GetTitle()
        if menu_title == "登录":
            self.login_panel.Hide()
            self.register_panel.Hide()
            self.login_panel.Show()
            self.Layout()

    # 点击菜单检测
    def click_menu(self, event):
        menu_id = event.GetId()
        if menu_id == self.register_id:
            self.login_panel.Hide()
            self.register_panel.Hide()
            self.register_panel.Show()
            self.Layout()
        elif menu_id == self.set_server_id:
            self.login_panel.Hide()
            self.register_panel.Hide()
            self.Layout()

    def login_page_receive(self, receive_content):
        if receive_content["genre"] == '登录':
            match receive_content["data"]['status']:
                case 0:
                    self.Destroy()
                    multiprocessing.Process(target=open_chat_window, args=(receive_content["data"]['account'],)).start()
                case -1:
                    wx.MessageBox('重复登录', '登录', wx.OK | wx.ICON_INFORMATION)
                case 1:
                    wx.MessageBox('密码错误', '登录', wx.OK | wx.ICON_INFORMATION)
                case 2:
                    wx.MessageBox('未找到该账号', '登录', wx.OK | wx.ICON_INFORMATION)
        elif receive_content["genre"] == '注册':
            wx.MessageBox(
                f'注册成功\n网名 : {receive_content["data"]['NetName']} \n账号 : {receive_content["data"]['Id']} \n密码 : {receive_content["data"]['Password']}',
                '注册', wx.OK | wx.ICON_INFORMATION)

    def send_login_button(self, event):
        if self.server_status:
            account = self.login_panel.LoginPanel_account_text.GetValue().strip()
            password = self.login_panel.LoginPanel_password_text.GetValue().strip()
            content = {'account': account, 'password': password}
            target = "服务器"
            genre = "登录"
            data = {"genre": genre, "target": target, "content": content}
            if account and password:
                self.Process_client_send("Session_server", "send_server", data)
            time.sleep(3)

    def send_register_button(self, event):
        if self.server_status:
            account = self.register_panel.RegisterPanel_account_text.GetValue().strip()
            password = self.register_panel.RegisterPanel_password_text.GetValue().strip()
            content = {'account': account, 'password': password}
            target = "服务器"
            genre = "注册"
            data = {"genre": genre, "target": target, "content": content}
            if account and password:
                self.Process_client_send("Session_server", "send_server", data)
            time.sleep(3)

    def Process_client_pick(self, data):
        if data['target'] in ['ALL', 'Login']:
            match data['function']:
                case 'server_status':
                    self.server_status = data['content']
                case 'login_page_receive':
                    self.login_page_receive(data['content'])



class LoginPanel(wx.Panel):
    def __init__(self, parent):
        super().__init__(parent)
        # 主盒子
        LoginPanel_main_box = wx.BoxSizer(wx.VERTICAL)

        # 顶部盒子,目前只放了软件名
        LoginPanel_top_box = wx.BoxSizer(wx.VERTICAL)  # 使用垂直盒子
        LoginPanel_show_title = wx.StaticText(self, label='登录')
        LoginPanel_show_title.SetFont(wx.Font(30, wx.FONTFAMILY_DEFAULT, wx.FONTSTYLE_NORMAL, wx.FONTWEIGHT_NORMAL))
        LoginPanel_top_box.Add(LoginPanel_show_title, 1, wx.ALIGN_CENTER_HORIZONTAL | wx.ALL, 10)
        LoginPanel_main_box.Add(LoginPanel_top_box, 0, wx.EXPAND)

        # 中部盒子,放账号和密码
        LoginPanel_content_box = wx.BoxSizer(wx.VERTICAL)
        # 账号
        LoginPanel_account_box = wx.BoxSizer(wx.HORIZONTAL)
        LoginPanel_account_label = wx.StaticText(self, label=' 账号:')
        LoginPanel_account_label.SetFont(
            wx.Font(15, wx.FONTFAMILY_DEFAULT, wx.FONTSTYLE_NORMAL, wx.FONTWEIGHT_NORMAL))
        LoginPanel_account_box.Add(LoginPanel_account_label, 0, wx.ALIGN_CENTER_VERTICAL)
        self.LoginPanel_account_text = wx.TextCtrl(self, size=(300, 30))
        self.LoginPanel_account_text.SetHint('请输入账号')
        LoginPanel_account_box.Add(self.LoginPanel_account_text, 1, wx.ALIGN_CENTER_VERTICAL)
        LoginPanel_content_box.Add(LoginPanel_account_box)
        # 添加空白控件来增加间距
        LoginPanel_content_box.Add(wx.StaticText(self, label=''), 0, wx.ALL, 5)
        # 密码
        LoginPanel_password_box = wx.BoxSizer(wx.HORIZONTAL)
        LoginPanel_password_label = wx.StaticText(self, label=' 密码:')
        LoginPanel_password_label.SetFont(
            wx.Font(15, wx.FONTFAMILY_DEFAULT, wx.FONTSTYLE_NORMAL, wx.FONTWEIGHT_NORMAL))
        LoginPanel_password_box.Add(LoginPanel_password_label, 0, wx.ALIGN_CENTER_VERTICAL)
        self.LoginPanel_password_text = wx.TextCtrl(self, size=(300, 30))
        self.LoginPanel_password_text.SetHint('请输入密码')
        LoginPanel_password_box.Add(self.LoginPanel_password_text, 1, wx.ALIGN_CENTER_VERTICAL)
        LoginPanel_content_box.Add(LoginPanel_password_box)
        LoginPanel_main_box.Add(LoginPanel_content_box, 0, wx.EXPAND)

        # 底部盒子
        LoginPanel_bottom_box = wx.BoxSizer(wx.VERTICAL)
        # 登录按钮
        LoginPanel_login_box = wx.BoxSizer(wx.VERTICAL)  # 使用垂直盒子布局
        self.LoginPanel_login_label = wx.Button(self, size=(200, 50), label='登录')
        LoginPanel_login_box.AddStretchSpacer()  # 添加一个可伸缩的空间，将登录按钮推到垂直中间
        LoginPanel_login_box.Add(self.LoginPanel_login_label, 0, wx.ALIGN_CENTER_HORIZONTAL)  # 将登录按钮添加到垂直盒子中
        LoginPanel_login_box.AddStretchSpacer()  # 再次添加一个可伸缩的空间，将登录按钮推到垂直中间
        LoginPanel_bottom_box.Add(LoginPanel_login_box, 1,
                                  wx.ALIGN_CENTER_VERTICAL | wx.ALIGN_CENTER_HORIZONTAL)  # 将垂直盒子添加到底部盒子中，设置垂直和水平居中对齐
        LoginPanel_main_box.Add(LoginPanel_bottom_box, 1, wx.EXPAND)  # 将底部盒子添加到主盒子中，使其填满剩余空间

        self.SetSizer(LoginPanel_main_box)


class RegisterPanel(wx.Panel):
    def __init__(self, parent):
        super().__init__(parent)

        # 主盒子
        RegisterPanel_main_box = wx.BoxSizer(wx.VERTICAL)

        # 顶部盒子,目前只放了软件名
        RegisterPanel_top_box = wx.BoxSizer(wx.VERTICAL)  # 使用垂直盒子
        RegisterPanel_show_title = wx.StaticText(self, label='注册')
        RegisterPanel_show_title.SetFont(
            wx.Font(30, wx.FONTFAMILY_DEFAULT, wx.FONTSTYLE_NORMAL, wx.FONTWEIGHT_NORMAL))
        RegisterPanel_top_box.Add(RegisterPanel_show_title, 1, wx.ALIGN_CENTER_HORIZONTAL | wx.ALL, 10)
        RegisterPanel_main_box.Add(RegisterPanel_top_box, 0, wx.EXPAND)

        # 中部盒子,放账号和密码
        RegisterPanel_content_box = wx.BoxSizer(wx.VERTICAL)
        # 账号
        RegisterPanel_account_box = wx.BoxSizer(wx.HORIZONTAL)
        RegisterPanel_account_label = wx.StaticText(self, label=' 用户名:')
        RegisterPanel_account_label.SetFont(
            wx.Font(15, wx.FONTFAMILY_DEFAULT, wx.FONTSTYLE_NORMAL, wx.FONTWEIGHT_NORMAL))
        RegisterPanel_account_box.Add(RegisterPanel_account_label, 0, wx.ALIGN_CENTER_VERTICAL)
        self.RegisterPanel_account_text = wx.TextCtrl(self, size=(300, 30))
        self.RegisterPanel_account_text.SetHint('请输入用户名')
        RegisterPanel_account_box.Add(self.RegisterPanel_account_text, 1, wx.ALIGN_CENTER_VERTICAL)
        RegisterPanel_content_box.Add(RegisterPanel_account_box)
        # 添加空白控件来增加间距
        RegisterPanel_content_box.Add(wx.StaticText(self, label=''), 0, wx.ALL, 5)
        # 密码
        RegisterPanel_password_box = wx.BoxSizer(wx.HORIZONTAL)
        RegisterPanel_password_label = wx.StaticText(self, label=' 密码:  ')
        RegisterPanel_password_label.SetFont(
            wx.Font(15, wx.FONTFAMILY_DEFAULT, wx.FONTSTYLE_NORMAL, wx.FONTWEIGHT_NORMAL))
        RegisterPanel_password_box.Add(RegisterPanel_password_label, 0, wx.ALIGN_CENTER_VERTICAL)
        self.RegisterPanel_password_text = wx.TextCtrl(self, size=(300, 30))
        self.RegisterPanel_password_text.SetHint('请输入密码')
        RegisterPanel_password_box.Add(self.RegisterPanel_password_text, 1, wx.ALIGN_CENTER_VERTICAL)
        RegisterPanel_content_box.Add(RegisterPanel_password_box)
        RegisterPanel_main_box.Add(RegisterPanel_content_box, 0, wx.EXPAND)

        # 底部盒子
        RegisterPanel_bottom_box = wx.BoxSizer(wx.VERTICAL)
        # 登录按钮
        RegisterPanel_register_box = wx.BoxSizer(wx.VERTICAL)  # 使用垂直盒子布局
        self.RegisterPanel_login_label = wx.Button(self, size=(200, 50), label='确认')
        RegisterPanel_register_box.AddStretchSpacer()  # 添加一个可伸缩的空间，将登录按钮推到垂直中间
        RegisterPanel_register_box.Add(self.RegisterPanel_login_label, 0,
                                       wx.ALIGN_CENTER_HORIZONTAL)  # 将登录按钮添加到垂直盒子中
        RegisterPanel_register_box.AddStretchSpacer()  # 再次添加一个可伸缩的空间，将登录按钮推到垂直中间
        RegisterPanel_bottom_box.Add(RegisterPanel_register_box, 1,
                                     wx.ALIGN_CENTER_VERTICAL | wx.ALIGN_CENTER_HORIZONTAL)  # 将垂直盒子添加到底部盒子中，设置垂直和水平居中对齐
        RegisterPanel_main_box.Add(RegisterPanel_bottom_box, 1, wx.EXPAND)  # 将底部盒子添加到主盒子中，使其填满剩余空间

        self.SetSizer(RegisterPanel_main_box)
