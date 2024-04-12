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
            account = self.login_panel.RegisterPanel_account_text.GetValue().strip()
            password = self.login_panel.RegisterPanel_password_text.GetValue().strip()
            content = {'account': account, 'password': password}
            target = "服务器"
            genre = "注册"
            self.send_server(genre=genre, target=target, content=content)
