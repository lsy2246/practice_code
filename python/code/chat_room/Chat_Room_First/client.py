import threading
from multiprocessing import Queue
from socket import AF_INET, SOCK_STREAM, socket
from threading import Thread
import wx


class MyFrame(wx.Frame):
    def __init__(self, client_name):
        # 调用父类的初始化方法
        # None没有父级窗口
        # id:表示当前窗口的一个编号
        # pos：窗口打开的位置
        # size:窗口的大小,单位是像素,400宽,450高
        wx.Frame.__init__(self, None, id=7878, title=client_name + '的客户端', pos=wx.DefaultPosition, size=(400, 500))

        # 创建面板对象
        panel = wx.Panel(self)

        # 在面板上放上盒子
        box = wx.BoxSizer(wx.VERTICAL)  # 垂直方向

        # 可伸缩网格
        grid1 = wx.FlexGridSizer(wx.HSCROLL)  # 方向水平布局
        # 创建两个按钮
        conn_link = wx.Button(panel, size=(200, 40), label="连接")
        conn_link_dis = wx.Button(panel, size=(200, 40), label="断开")
        # 把按钮放在可伸缩网格
        grid1.Add(conn_link, 0, wx.TOP | wx.LEFT)
        grid1.Add(conn_link_dis, 0, wx.TOP | wx.RIGHT)
        # 可伸缩网格添加到盒子
        box.Add(grid1, 1, wx.ALIGN_CENTER)

        # 只读文本框,显示聊天内容
        self.show_text = wx.TextCtrl(panel, size=(400, 210), style=wx.TE_MULTILINE | wx.TE_READONLY)
        box.Add(self.show_text, 1, wx.ALIGN_CENTER)

        # 创建聊天内容
        self.chat_text = wx.TextCtrl(panel, size=(400, 120), style=wx.TE_MULTILINE)
        box.Add(self.chat_text, 1, wx.ALIGN_CENTER)

        # 可伸缩网格
        grid2 = wx.FlexGridSizer(wx.HSCROLL)  # 方向水平布局
        # 创建两个按钮
        conn_reset = wx.Button(panel, size=(200, 40), label="重置")
        conn_send = wx.Button(panel, size=(200, 40), label="发送")
        # 把按钮放在可伸缩网格
        grid2.Add(conn_reset, 0, wx.TOP | wx.LEFT)
        grid2.Add(conn_send, 0, wx.TOP | wx.RIGHT)
        # 可伸缩网格添加到盒子
        box.Add(grid2, 1, wx.ALIGN_CENTER)

        panel.SetSizer(box)

        """—————————按钮绑定操作—————————"""
        self.Bind(wx.EVT_BUTTON, self.link_server, conn_link)
        self.client_name = client_name
        self.state = False
        self.server_socket = None
        self.server_host_port = ('localhost', 8787)  # 空代表的是本机IP

        self.Bind(wx.EVT_BUTTON, self.send_data, conn_send)
        self.Bind(wx.EVT_BUTTON, self.stop_server, conn_link_dis)
        self.Bind(wx.EVT_BUTTON, self.reset_screen, conn_reset)

    def link_server(self, event):
        if not self.state:
            self.server_socket = socket(AF_INET, SOCK_STREAM)
            self.server_socket.connect(self.server_host_port)
            self.server_socket.send(self.client_name.encode('utf-8'))
            recv_thread = threading.Thread(target=self.recv_data)
            recv_thread.daemon = True
            self.state = True
            recv_thread.start()

    def stop_server(self, event):
        if self.state:
            self.server_socket.send('client-exit'.encode('utf-8'))
            self.show_text.AppendText('-' * 40 + '\n' + "成功与服务器断开连接" + '\n')
            self.state = False

    def reset_screen(self, event):
        self.show_text.Clear()

    def recv_data(self):
        if self.state:
            show_info = self.server_socket.recv(1024).decode('utf-8')
            self.show_text.AppendText('-' * 40 + '\n' + show_info + '\n')

    def send_data(self, event):
        if self.state:
            input_data = self.chat_text.GetValue()
            if input_data != "":
                self.server_socket.send(input_data.encode('utf-8'))
                self.chat_text.SetValue('')


if __name__ == '__main__':
    # 初始化app()
    app = wx.App()
    # 创建直接的客户端对象
    frame = MyFrame("lsy").Show()

    # 循环刷新显示
    app.MainLoop()
