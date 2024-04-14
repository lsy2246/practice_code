from .Login import *
from .Session_server import *


class Client_main(LoginFrame, Session_server):
    def __init__(self):
        Session_server.__init__(self)  # 与服务器会话
        LoginFrame.__init__(self)

        # 主页按钮绑定
        self.Bind(wx.EVT_BUTTON, self.send_login_button, self.login_panel.LoginPanel_login_label)
        self.Bind(wx.EVT_BUTTON, self.send_register_button, self.register_panel.RegisterPanel_login_label)

    def send_login_button(self, event):
        if self.server_status:
            account = self.login_panel.LoginPanel_account_text.GetValue().strip()
            password = self.login_panel.LoginPanel_password_text.GetValue().strip()
            content = {'account': account, 'password': password}
            target = "服务器"
            genre = "登录"
            self.send_server(genre=genre, target=target, content=content)

    def send_register_button(self, event):
        if self.server_status:
            account = self.register_panel.RegisterPanel_account_text.GetValue().strip()
            password = self.register_panel.RegisterPanel_password_text.GetValue().strip()
            content = {'account': account, 'password': password}
            target = "服务器"
            genre = "注册"
            self.send_server(genre=genre, target=target, content=content)

    def login_page_receive(self, receive_content):
        if receive_content["genre"] == '登录':
            match receive_content["data"]:
                case 0:
                    wx.MessageBox('登录成功', '登录', wx.OK | wx.ICON_INFORMATION)
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


