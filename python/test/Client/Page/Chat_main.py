import wx
import wx.aui
import wx.lib.scrolledpanel as scrolled
import time
import multiprocessing
import os
import csv
from Client.Transmission.Process_Client import ProcessClient


class ChatFrame(wx.Frame, ProcessClient):
    def __init__(self, Id):
        wx.Frame().__init__(None, size=(800, 600), title="账号:  " + str(Id))
        ProcessClient.__init__(self)

        self.detection_data(Id)

        ChatMain_Panel = wx.Panel(self, style=wx.BORDER_SUNKEN)
        ChatMain_box = wx.BoxSizer(wx.HORIZONTAL)
        ChatMain_Panel.SetSizer(ChatMain_box)

        Function_Panel = wx.Panel(ChatMain_Panel, style=wx.BORDER_RAISED)
        Function_box = wx.BoxSizer(wx.VERTICAL)
        Function_Panel.SetSizer(Function_box)
        Function_Panel.SetBackgroundColour(wx.Colour(240, 240, 240))

        image_chat = r'./Client/image/chat.png'
        Chat_bitmap = wx.Bitmap(image_chat, wx.BITMAP_TYPE_PNG)
        Chat_bitmap_static = wx.StaticBitmap(Function_Panel, bitmap=Chat_bitmap, style=wx.BORDER_RAISED)
        Chat_bitmap_static.SetToolTip("聊天")
        Function_box.Add(Chat_bitmap_static, 1, wx.EXPAND, 0)
        Chat_bitmap_static.Bind(wx.EVT_LEFT_DOWN, self.click_chat_button)

        Function_box.AddSpacer(20)  # 调整这个数字以改变间距大小

        image_connect = r'./Client/image/connect.png'
        connect_bitmap = wx.Bitmap(image_connect, wx.BITMAP_TYPE_PNG)
        connect_bitmap_static = wx.StaticBitmap(Function_Panel, bitmap=connect_bitmap, style=wx.BORDER_RAISED)
        connect_bitmap_static.SetToolTip("通讯录")
        Function_box.Add(connect_bitmap_static, 1, wx.EXPAND, 0)
        connect_bitmap_static.Bind(wx.EVT_LEFT_DOWN, self.click_connect_button)

        Function_box.AddSpacer(20)  # 调整这个数字以改变间距大小

        image_find = r'./Client/image/find.png'
        find_bitmap = wx.Bitmap(image_find, wx.BITMAP_TYPE_PNG)
        find_bitmap_static = wx.StaticBitmap(Function_Panel, bitmap=find_bitmap, style=wx.BORDER_RAISED)
        find_bitmap_static.SetToolTip("查找")
        Function_box.Add(find_bitmap_static, 1, wx.EXPAND, 0)
        find_bitmap_static.Bind(wx.EVT_LEFT_DOWN, self.click_find_button)

        Function_box.AddSpacer(280)  # 调整这个数字以改变间距大小

        image_site = r'./Client/image/site.png'
        site_bitmap = wx.Bitmap(image_site, wx.BITMAP_TYPE_PNG)
        site_bitmap_static = wx.StaticBitmap(Function_Panel, bitmap=site_bitmap, style=wx.BORDER_RAISED)
        site_bitmap_static.SetToolTip("设置")
        Function_box.Add(site_bitmap_static, 1, wx.EXPAND, 0)
        site_bitmap_static.Bind(wx.EVT_LEFT_DOWN, self.click_site_button)

        Function_box.Fit(Function_Panel)  # 调整面板大小以适应图像

        ChatMain_box.Add(Function_Panel, 0, wx.EXPAND | wx.ALL, 5)

        operate_box = wx.BoxSizer(wx.VERTICAL)

        self.chat_page = self.ChatPage(ChatMain_Panel)  # 将 ChatMain_Panel 作为 ChatPage 的 parent
        operate_box.Add(self.chat_page, 1, wx.EXPAND, 5)
        self.chat_page.Hide()

        self.connect_page = self.ConnectPage(ChatMain_Panel)
        operate_box.Add(self.connect_page, 1, wx.EXPAND, 5)
        self.connect_page.Hide()

        self.site_page = self.SitePage(ChatMain_Panel)
        operate_box.Add(self.site_page, 1, wx.EXPAND, 5)
        self.site_page.Hide()

        self.find_page = self.FindPage(ChatMain_Panel)
        operate_box.Add(self.find_page, 1, wx.EXPAND, 5)
        self.find_page.Hide()

        ChatMain_box.Add(operate_box, 1, wx.EXPAND, 5)

        self.chat_page.Show()

        ChatMain_Panel.SetSizer(ChatMain_box)

    def click_chat_button(self, event):
        self.chat_page.Hide()
        self.connect_page.Hide()
        self.site_page.Hide()
        self.find_page.Hide()
        self.chat_page.Show()
        self.Layout()

    def click_connect_button(self, event):
        self.chat_page.Hide()
        self.connect_page.Hide()
        self.site_page.Hide()
        self.find_page.Hide()
        self.connect_page.Show()
        self.Layout()

    def click_site_button(self, event):
        self.chat_page.Hide()
        self.connect_page.Hide()
        self.site_page.Hide()
        self.find_page.Hide()
        self.site_page.Show()
        self.Layout()

    def click_find_button(self, event):
        self.chat_page.Hide()
        self.connect_page.Hide()
        self.site_page.Hide()
        self.find_page.Hide()
        self.find_page.Show()
        self.Layout()

    def detection_data(self, Id):
        root_path = rf'.\{Id}'
        info_path = root_path + r'\info.csv'
        file_root_path = root_path + r'\file'
        other_file_path = file_root_path + r'\other'
        image_file_path = file_root_path + r'\image'
        if not os.path.isdir(root_path):
            os.mkdir(root_path)
        if not os.path.isdir(file_root_path):
            os.mkdir(file_root_path)
            os.mkdir(other_file_path)
            os.mkdir(image_file_path)
        if not os.path.exists(info_path):
            with open(info_path, 'w', encoding='utf-8') as f:
                pass
        with open(info_path, 'r+', encoding='utf-8') as info:
            if info.tell() == 0:
                date = None
            target = "服务器"
            genre = "数据更新"
            content = date
            data = {"genre": genre, "target": target, "content": content}
            self.Process_client_send("Session_server", "send_server", data)

    class ChatPage(wx.Panel):
        def __init__(self, parent):
            wx.Panel.__init__(self, parent, style=wx.BORDER_SUNKEN)
            ChatPage_main_box = wx.BoxSizer(wx.HORIZONTAL)
            self.chat_window_id = []

            ChatPage_Contact_person_box = wx.BoxSizer(wx.VERTICAL)
            self.ChatPage_Contact_person_panel = scrolled.ScrolledPanel(self, -1, style=wx.SUNKEN_BORDER)
            self.ChatPage_Contact_person_panel.SetupScrolling()  # 启用滚动功能
            self.ChatPage_Contact_person_panel.SetSizer(wx.BoxSizer(wx.VERTICAL))
            ChatPage_Contact_person_box.Add(self.ChatPage_Contact_person_panel, proportion=1, flag=wx.EXPAND | wx.ALL,
                                            border=5)
            ChatPage_main_box.Add(ChatPage_Contact_person_box, proportion=1, flag=wx.EXPAND | wx.ALL, border=5)

            self.chat_tab = wx.aui.AuiNotebook(self, style=wx.aui.AUI_NB_CLOSE_ON_ALL_TABS)
            ChatPage_main_box.Add(self.chat_tab, proportion=3, flag=wx.EXPAND | wx.ALL, border=5)

            self.SetSizer(ChatPage_main_box)

        def ChatPage_add_Contact_person(self, Id, Remark, info):
            ChatPage_add_Contact_person_box = wx.BoxSizer(wx.VERTICAL)

            ChatPage_add_Contact_person_top_box = wx.BoxSizer(wx.HORIZONTAL)
            if len(Remark) > 6:
                Remark = Remark[:6] + "..."
            else:
                Remark += ''.join([" " for i in range(max(0, 9 - len(Remark)))])
            ChatPage_add_Contact_person_NetName = wx.StaticText(self.ChatPage_Contact_person_panel, -1, Remark)
            ChatPage_add_Contact_person_top_box.Add(ChatPage_add_Contact_person_NetName, 0, wx.ALIGN_LEFT, 0)

            ChatPage_add_Contact_person_top_box.AddSpacer(20)

            ChatPage_add_Contact_person_date = wx.StaticText(self.ChatPage_Contact_person_panel, -1,
                                                             time.strftime("%Y/%m/%d", time.localtime()))
            ChatPage_add_Contact_person_top_box.Add(ChatPage_add_Contact_person_date, 0, wx.ALIGN_CENTER_VERTICAL, 0)
            ChatPage_add_Contact_person_box.Add(ChatPage_add_Contact_person_top_box, 0, wx.EXPAND, 0)

            if len(info) > 10:
                info = info[:10] + "..."
            ChatPage_add_Contact_person_info = wx.StaticText(self.ChatPage_Contact_person_panel, -1, info)
            ChatPage_add_Contact_person_box.Add(ChatPage_add_Contact_person_info, 0, wx.ALIGN_LEFT, 0)

            self.ChatPage_Contact_person_panel.GetSizer().Add(ChatPage_add_Contact_person_box, 0, wx.ALL, 5)
            self.ChatPage_Contact_person_panel.Layout()
            self.ChatPage_Contact_person_panel.SetupScrolling()

            ChatPage_add_Contact_person_NetName.Bind(wx.EVT_LEFT_DOWN,
                                                     lambda event: self.ChatPage_add_Contact_tab(Id, Remark))

        def ChatPage_add_Contact_tab(self, Id, Remark):
            if Id in self.chat_window_id:
                return
            self.chat_window_id.append(Id)

            chat_panel = wx.Panel(self.chat_tab)
            chat_box = wx.BoxSizer(wx.VERTICAL)

            chat_receive_box = wx.BoxSizer(wx.HORIZONTAL)
            chat_receive_text = wx.TextCtrl(chat_panel, style=wx.TE_MULTILINE | wx.TE_READONLY)
            chat_receive_box.Add(chat_receive_text, 1, wx.EXPAND, 0)
            chat_box.Add(chat_receive_box, 2, wx.EXPAND, 0)

            toolbar = wx.ToolBar(chat_panel)
            toolbar.SetToolBitmapSize((16, 16))  # Set the size of the toolbar icons
            toolbar.AddTool(wx.ID_ANY, "Tool", wx.Bitmap(wx.Bitmap(r'./Client/image/picture.png')))
            toolbar.AddTool(wx.ID_ANY, "Tool", wx.Bitmap(wx.Bitmap(r'./Client/image/file.png')))
            toolbar.AddTool(wx.ID_ANY, "Tool", wx.Bitmap(wx.Bitmap(r'./Client/image/speech.png')))
            toolbar.AddTool(wx.ID_ANY, "Tool", wx.Bitmap(wx.Bitmap(r'./Client/image/video.png')))
            toolbar.Realize()
            toolbar.SetSize((-1, 30))  # Set the size of the toolbar
            chat_box.Add(toolbar, 0, wx.EXPAND)

            chat_send_box = wx.BoxSizer(wx.HORIZONTAL)
            chat_send_text = wx.TextCtrl(chat_panel, style=wx.TE_MULTILINE)
            chat_send_box.Add(chat_send_text, 1, wx.EXPAND, 0)
            chat_box.Add(chat_send_box, 1, wx.EXPAND, 0)

            send_button = wx.Button(chat_panel, label='发送')  # Create a send button
            chat_send_box.Add(send_button, 0, wx.EXPAND | wx.LEFT, 5)  # Add the button to the send box

            chat_panel.SetSizer(chat_box)

            self.chat_tab.AddPage(chat_panel, Remark, select=True)
            self.GetParent().contact_windows[Id] = chat_panel

    class ConnectPage(wx.Panel):
        def __init__(self, parent):
            wx.Panel.__init__(self, parent)
            print("联系人")

    class SitePage(wx.Panel):
        def __init__(self, parent):
            wx.Panel.__init__(self, parent)
            print("设置")

    class FindPage(wx.Panel):
        def __init__(self, parent):
            wx.Panel.__init__(self, parent)
            print("查找")