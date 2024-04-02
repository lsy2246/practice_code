import threading
import time
from socket import AF_INET, SOCK_STREAM, socket
from multiprocessing import Queue
from threading import Thread
import wx
import os

class Myserver(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, id=8787, title="Server", pos=wx.DefaultPosition, size=(400, 500))

        panel = wx.Panel(self)

        box = wx.BoxSizer(wx.VERTICAL)

        grid = wx.FlexGridSizer(wx.HSCROLL)

        conn_start = wx.Button(panel, size=(133, 40), label="启动")
        conn_save = wx.Button(panel, size=(133, 40), label="保存")
        conn_stop = wx.Button(panel, size=(133, 40), label="停止")

        grid.Add(conn_start, 0, wx.TOP)
        grid.Add(conn_save, 0, wx.TOP)
        grid.Add(conn_stop, 0, wx.TOP)

        box.Add(grid, 0, wx.ALIGN_CENTER)

        self.show_text = wx.TextCtrl(panel, size=(400, 450), style=wx.TE_MULTILINE | wx.TE_READONLY)
        box.Add(self.show_text, 0, wx.ALIGN_CENTER)

        panel.SetSizer(box)

        """—————————服务器的必要属性—————————"""
        self.state = False  # 储存服务器的启动状态,默认值为False
        self.host_port = ('localhost', 8787)  # 空代表的是本机IP
        # 创建socket对象
        self.server_socket = socket(AF_INET, SOCK_STREAM)
        # 绑定IP地址和端口
        self.server_socket.bind(self.host_port)
        # 监听
        self.server_socket.listen()
        # 储存一个字典,储存客户端对话的会话线程
        self.server_thread_dict = {}

        """—————————按钮绑定操作—————————"""
        self.Bind(wx.EVT_BUTTON, self.start_server, conn_start)
        self.Bind(wx.EVT_BUTTON, self.save_data, conn_save)
        self.Bind(wx.EVT_BUTTON, self.stop_server, conn_stop)

    def start_server(self, event):
        # 首先判断服务器是否已近启动
        if not self.state:
            # 创建主线程
            main_thread = Thread(target=self.server_main)
            # 设置为守护线程,父线程(窗体)执行结束后子线程也自动关闭
            main_thread.daemon = True
            # 修改服务器状态
            self.state = True
            # 启动主线程
            main_thread.start()

    def server_main(self):
        # 判断服务器启动状态
        while self.state:
            # 输出服务器成功启动
            self.show_text.AppendText('-' * 40 + '\n服务器启动成功\n')
            # 接收服务器的请求
            client_socket, client_addr = self.server_socket.accept()
            # 客户端发送请求后第一个请求,发送过来的第一条数据为客户端的名称,客户端的名称作为字典的键
            user_name = client_socket.recv(1024).decode('utf-8')
            # 创建一个会话线程
            session_thread = SessionThread(client_socket, user_name, self)
            # 储存到字典
            self.server_thread_dict[user_name] = session_thread
            # 启动会话线程
            session_thread.start()
            # 输出服务器的提示信息
            self.show_info_and_send_client('服务器通知', f"欢迎{user_name}进入聊天室",
                                           time.strftime('%Y-%m-%d %H:%M:%S', time.localtime()))

        self.server_socket.close()

    def show_info_and_send_client(self, data_source, data, datatime):
        if self.state:
            show_info = f"{data_source}: {data}\n时间:{datatime}"
            self.show_text.AppendText('-' * 40 + '\n' + show_info + '\n')
            for client in self.server_thread_dict.values():
                if client.state:
                    client.client_socket.send(show_info.encode('utf-8'))

    def save_data(self, event):
        time_now = time.strftime('%Y-%m-%d_%H-%M-%S', time.localtime())
        if not os.path.exists('chat data'):
            os.mkdir('chat data')
        with open(rf"chat data\{time_now}.txt", 'w+') as f:
            data = self.show_text.GetValue()
            f.write(data)
        self.show_text.AppendText(rf"文件成功保存在\chat data\{time_now}.txt")

    def stop_server(self, event):
        if self.state:
            self.show_info_and_send_client('服务器通知', "服务器关闭",
                                           time.strftime('%Y-%m-%d %H:%M:%S', time.localtime()))
            self.show_text.AppendText('服务器通知 服务器关闭' +
                                      time.strftime('%Y-%m-%d %H:%M:%S', time.localtime()))
            self.state = False


class SessionThread(threading.Thread):
    def __init__(self, client_socket, user_name, server):
        # 调用父类的初始方法
        threading.Thread.__init__(self)
        self.client_socket = client_socket
        self.user_name = user_name
        self.server = server
        self.state = True  # 会话线程是否启动,当创建线程自动启动

    def run(self) -> None:
        while self.state:
            # 从客户端接收数据,存储在data中
            data = self.client_socket.recv(1024).decode('utf-8')
            # 如果客户端点击断开连接,先给服务器发送一句话,消息自定义
            if data == 'client-exit':
                self.server.show_info_and_send_client('服务器通知', f"{self.user_name}退出了聊天室",
                                                      time.strftime('%Y-%m-%d %H:%M:%S', time.localtime()))
                self.state = False
            else:
                print(data)
                print(self.user_name)
                self.server.show_info_and_send_client(self.user_name, data,
                                                      time.strftime('%Y-%m-%d %H:%M:%S', time.localtime()))

        # 关闭socket连接
        self.client_socket.close()


if __name__ == '__main__':
    # 初始化app()
    app = wx.App()
    # 创建直接的客户端对象
    frame = Myserver()
    frame.Show()

    # 循环刷新显示
    app.MainLoop()
