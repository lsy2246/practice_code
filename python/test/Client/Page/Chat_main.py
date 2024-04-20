import wx.richtext as rt
import os
import wx
import time
import multiprocessing

from Client.Transmission.Process_Client import ProcessClient


class ChatFrame(wx.Frame, ProcessClient):
    def __init__(self, Id):
        wx.Frame.__init__(self, None, size=(800, 600), title="账号:  " + str(Id))
        ProcessClient.__init__(self)
        self.userid = Id

        current_file_path = __file__
        current_file_name = os.path.basename(current_file_path).split('.')[0]
        self.Process_client_send("Server", "Name", current_file_name)

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

        self.Process_client_send("File_operate", "read_data", None)

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

    def Process_client_pick(self, data):
        if data['target'] in ['ALL', 'Chat_main']:
            match data['function']:
                case 'ChatPage_add_Contact_person':
                    data = data['content']
                    Contact = data['Contact']
                    Remark = data['Remark']
                    Time = data['UpDataTime']
                    wx.CallAfter(self.chat_page.ChatPage_add_Contact_person, Contact, Remark)
                case 'Chat_screen_show':
                    Contact = None
                    data = data['content']
                    send = data['Send']
                    receive = data['Receive']
                    Type = data['Type']
                    content = data['Content']
                    UpDataTime = data['Time']
                    if send == str(self.userid):
                        Contact = receive
                    elif receive == str(self.userid):
                        Contact = send
                    wx.CallAfter(self.chat_page.Chat_screen_show, Contact, send, receive, Type, content, UpDataTime)

    class ChatPage(wx.Panel):
        def __init__(self, parent):
            wx.Panel.__init__(self, parent, style=wx.BORDER_SUNKEN)

            ChatPage_main_box = wx.BoxSizer(wx.HORIZONTAL)
            self.chat_page_map = {}
            self.chat_page_ids = []
            self.current_chat_page = None  # 新增的属性用于跟踪当前显示的聊天面板

            self.ChatPage_Listbook = wx.Listbook(self, style=wx.LB_LEFT)
            self.ChatPage_Listbook.Bind(wx.EVT_LISTBOOK_PAGE_CHANGED, self.on_page_changed)

            ChatPage_main_box.Add(self.ChatPage_Listbook, 1, wx.EXPAND, 0)
            self.SetSizer(ChatPage_main_box)

        def ChatPage_add_Contact_person(self, Id, Remark):
            contact_page = wx.Panel(self.ChatPage_Listbook)
            self.ChatPage_Listbook.AddPage(contact_page, Remark)
            chat_page = self.ChatPage_add_Contact_tab(Id)

            self.chat_page_map[Id] = chat_page
            self.chat_page_ids.append(Id)
            # 隐藏当前的聊天面板
            if self.current_chat_page:
                self.current_chat_page.Hide()
            # 将新的聊天面板添加到ChatPage_main_box中
            self.GetSizer().Add(chat_page, 5, wx.EXPAND)
            # 显示新的聊天面板
            chat_page.Show()
            # 更新当前显示的聊天面板
            self.current_chat_page = chat_page
            chat_page.Show()
            # 重新布局
            self.Layout()

        def ChatPage_add_Contact_tab(self, Id):
            chat_panel = wx.Panel(self)
            chat_box = wx.BoxSizer(wx.VERTICAL)

            chat_panel.contact_id = Id

            chat_receive_box = wx.BoxSizer(wx.HORIZONTAL)
            chat_panel.chat_receive_text = rt.RichTextCtrl(chat_panel,
                                                           style=wx.VSCROLL | wx.HSCROLL | wx.NO_BORDER | wx.WANTS_CHARS)
            chat_receive_box.Add(chat_panel.chat_receive_text, 1, wx.EXPAND, 0)
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
            chat_panel.chat_send_text = wx.TextCtrl(chat_panel, style=wx.TE_MULTILINE)
            chat_send_box.Add(chat_panel.chat_send_text, 1, wx.EXPAND, 0)
            chat_box.Add(chat_send_box, 1, wx.EXPAND, 0)

            send_button = wx.Button(chat_panel, label='发送')  # Create a send button
            send_button.Bind(wx.EVT_BUTTON, self.on_send_button_click)
            chat_send_box.Add(send_button, 0, wx.EXPAND | wx.LEFT, 5)  # Add the button to the send box

            chat_panel.SetSizer(chat_box)

            return chat_panel

        def Chat_screen_show(self, Contact, send, receive, Type, data, UpDataTime):
            chat_panel = self.chat_page_map[Contact]
            if Type == 'text':
                # 确定对齐方式
                if Contact == receive:
                    alignment = wx.TEXT_ALIGNMENT_RIGHT
                else:
                    alignment = wx.TEXT_ALIGNMENT_LEFT
                # 开始设置对齐
                chat_panel.chat_receive_text.BeginAlignment(alignment)
                # 按每30个字符分割消息内容并写入
                contents = [data[i:i + 30] for i in range(0, len(data), 30)]
                contents.append(UpDataTime)  # 添加时间戳
                for content in contents:
                    chat_panel.chat_receive_text.WriteText(content + '\n')  # WriteText处理换行
                # 结束对齐设置
                chat_panel.chat_receive_text.EndAlignment()
                # 添加额外的新行（如果需要）
                chat_panel.chat_receive_text.Newline()

                # 在添加完所有消息后
                chat_panel.chat_receive_text.ShowPosition(chat_panel.chat_receive_text.GetLastPosition())
                chat_panel.Refresh()
                chat_panel.Update()
                self.Layout()

        def on_send_button_click(self, event):
            button = event.GetEventObject()
            chat_panel = button.GetParent()
            send_text = chat_panel.chat_send_text.GetValue()  # 正确获取输入框内容
            contact_id = str(chat_panel.contact_id)  # 获取联系人ID
            if send_text == '':
                return

            self.Chat_screen_show(contact_id, None, contact_id, 'text', send_text,
                                  time.strftime('%Y-%m-%d %H:%M:%S', time.localtime()))

            data = {"Type": "text", "content": send_text}

            content = {"genre": '聊天记录', "target": contact_id, "content": data}

            top_frame = self.GetTopLevelParent()

            top_frame.Process_client_send('Session_server', 'send_server', content)
            chat_panel.chat_send_text.SetValue('')  # 清空输入框
            event.Skip()

        def on_page_changed(self, event):
            # 获取当前选定的页面的索引
            current_page_index = self.ChatPage_Listbook.GetSelection()
            # 通过索引从chat_page_ids列表中获取对应的Id
            current_page_id = self.chat_page_ids[current_page_index]
            # 从chat_page_map中找到对应的聊天面板
            new_chat_page = self.chat_page_map[current_page_id]
            # 隐藏旧的聊天面板
            if self.current_chat_page:
                self.current_chat_page.Hide()
            # 显示新的聊天面板
            new_chat_page.Show()
            # 更新当前显示的聊天面板
            self.current_chat_page = new_chat_page
            # 重新布局
            self.Layout()
            # 处理完事件后，不要忘记调用event.Skip()，以便事件可以继续传播到其他处理器
            event.Skip()

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
