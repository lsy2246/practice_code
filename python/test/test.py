import wx
import wx.aui
import wx.lib.scrolledpanel as scrolled
import time


class ChatFrame(wx.Frame):
    def __init__(self):
        super().__init__(None, size=(1000, 700))

        ChatMain_Panel = wx.Panel(self, style=wx.BORDER_SUNKEN)
        ChatMain_box = wx.BoxSizer(wx.HORIZONTAL)
        ChatMain_Panel.SetSizer(ChatMain_box)

        Function_Panel = wx.Panel(ChatMain_Panel, style=wx.BORDER_RAISED)
        Function_box = wx.BoxSizer(wx.VERTICAL)
        Function_Panel.SetSizer(Function_box)
        Function_Panel.SetBackgroundColour(wx.Colour(242, 242, 242))

        image_chat = r'./Client/image/chat.png'
        Chat_bitmap = wx.Bitmap(image_chat, wx.BITMAP_TYPE_PNG)
        Chat_bitmap_static = wx.StaticBitmap(Function_Panel, bitmap=Chat_bitmap, style=wx.BORDER_RAISED)
        Chat_bitmap_static.SetToolTip("聊天")
        Function_box.Add(Chat_bitmap_static, 1, wx.EXPAND, 0)
        Chat_bitmap_static.Bind(wx.EVT_LEFT_DOWN, self.click_chat_button)

        Function_box.AddSpacer(30)  # 调整这个数字以改变间距大小

        image_connect = r'./Client/image/connect.png'
        connect_bitmap = wx.Bitmap(image_connect, wx.BITMAP_TYPE_PNG)
        connect_bitmap_static = wx.StaticBitmap(Function_Panel, bitmap=connect_bitmap, style=wx.BORDER_RAISED)
        connect_bitmap_static.SetToolTip("通讯录")
        Function_box.Add(connect_bitmap_static, 1, wx.EXPAND, 0)
        connect_bitmap_static.Bind(wx.EVT_LEFT_DOWN, self.click_connect_button)

        Function_box.AddSpacer(28)  # 调整这个数字以改变间距大小

        image_find = r'./Client/image/find.png'
        find_bitmap = wx.Bitmap(image_find, wx.BITMAP_TYPE_PNG)
        find_bitmap_static = wx.StaticBitmap(Function_Panel, bitmap=find_bitmap, style=wx.BORDER_RAISED)
        find_bitmap_static.SetToolTip("查找")
        Function_box.Add(find_bitmap_static, 1, wx.EXPAND, 0)
        find_bitmap_static.Bind(wx.EVT_LEFT_DOWN, self.click_find_button)

        Function_box.AddSpacer(340)  # 调整这个数字以改变间距大小

        image_site = r'./Client/image/site.png'
        site_bitmap = wx.Bitmap(image_site, wx.BITMAP_TYPE_PNG)
        site_bitmap_static = wx.StaticBitmap(Function_Panel, bitmap=site_bitmap, style=wx.BORDER_RAISED)
        site_bitmap_static.SetToolTip("设置")
        Function_box.Add(site_bitmap_static, 1, wx.EXPAND, 0)
        site_bitmap_static.Bind(wx.EVT_LEFT_DOWN, self.click_site_button)

        Function_box.Fit(Function_Panel)  # 调整面板大小以适应图像

        ChatMain_box.Add(Function_Panel, 0, wx.EXPAND | wx.ALL, 5)

        operate_box = wx.BoxSizer(wx.VERTICAL)

        chat_page = self.ChatPage(ChatMain_Panel)  # 将 ChatMain_Panel 作为 ChatPage 的 parent
        operate_box.Add(chat_page, 1, wx.EXPAND, 5)

        ChatMain_box.Add(operate_box, 1, wx.EXPAND, 5)

        ChatMain_Panel.SetSizer(ChatMain_box)

    def click_chat_button(self, event):
        print("点击了聊天")

    def click_connect_button(self, event):
        print("点击了联系人")

    def click_site_button(self, event):
        print("点击了设置")

    def click_find_button(self, event):
        print("点击了查找")

    class ChatPage(wx.Panel):
        def __init__(self, parent):
            wx.Panel.__init__(self, parent, style=wx.BORDER_SUNKEN)
            ChatPage_main_box = wx.BoxSizer(wx.HORIZONTAL)
            self.ChatPage_add_Contact_text_box_dick = {}

            ChatPage_Contact_person_box = wx.BoxSizer(wx.VERTICAL)
            self.ChatPage_Contact_person_panel = scrolled.ScrolledPanel(self, -1, style=wx.SUNKEN_BORDER)
            self.ChatPage_Contact_person_panel.SetupScrolling()  # 启用滚动功能
            self.ChatPage_Contact_person_panel.SetSizer(wx.BoxSizer(wx.VERTICAL))
            ChatPage_Contact_person_box.Add(self.ChatPage_Contact_person_panel, proportion=1, flag=wx.EXPAND | wx.ALL,
                                            border=5)
            ChatPage_main_box.Add(ChatPage_Contact_person_box, 1, wx.EXPAND, 5)

            self.ChatPage_add_Contact_person(11, "lsy", "asdasddsa")

            self.chat_tab = wx.aui.AuiNotebook(self,style=wx.aui.AUI_NB_CLOSE_ON_ALL_TABS)
            ChatPage_main_box.Add(self.chat_tab, 1, wx.EXPAND, 0)

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

            ChatPage_add_Contact_person_NetName.Bind(wx.EVT_LEFT_DOWN, lambda event: self.ChatPage_add_Contact_tab(Id, Remark))


        def ChatPage_add_Contact_tab(self, Id, Remark):
            for i in range(self.chat_tab.GetPageCount()):
                if self.chat_tab.GetPageText(i) == Remark:
                    return

            chat_panel = wx.Panel(self.chat_tab)
            chat_box = wx.BoxSizer(wx.VERTICAL)

            chat_receive_box = wx.BoxSizer(wx.HORIZONTAL)
            chat_receive_text = wx.TextCtrl(chat_panel, style=wx.TE_MULTILINE)
            chat_receive_box.Add(chat_receive_text, 0, wx.EXPAND, 0)

            chat_box.Add(chat_receive_box, 1, wx.EXPAND, 0)

            self.chat_tab.AddPage(chat_panel, wx.Panel(), Remark, select=True)  # 将第三个参数改为 wx.Panel()，表示每个页面使用一个新的 Panel 承载控件

            chat_panel.SetSizer(chat_box)

app = wx.App()
frame = ChatFrame()
frame.Show()
app.MainLoop()
