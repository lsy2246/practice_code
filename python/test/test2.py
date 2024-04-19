import wx

class ChatPanel(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent)

        sizer = wx.BoxSizer(wx.HORIZONTAL)

        self.listbook = wx.Listbook(self, style=wx.LB_LEFT)
        self.chat_pages = {}

        self.listbook.Bind(wx.EVT_LISTBOOK_PAGE_CHANGED, self.on_page_changed)

        sizer.Add(self.listbook, 1, wx.EXPAND)
        self.SetSizer(sizer)

    def add_contact(self, contact_name):
        contact_page = wx.Panel(self.listbook)
        wx.StaticText(contact_page, label=contact_name)
        self.listbook.AddPage(contact_page, contact_name)

        chat_page = self.create_chat_page()
        self.chat_pages[contact_name] = chat_page

        if self.listbook.GetPageCount() == 1:
            self.GetSizer().Add(chat_page, 3, wx.EXPAND)
            self.Layout()

    def create_chat_page(self):
        chat_page = wx.Panel(self)
        chat_sizer = wx.BoxSizer(wx.VERTICAL)

        chat_page.chat_text = wx.TextCtrl(chat_page, style=wx.TE_MULTILINE | wx.TE_READONLY)
        chat_sizer.Add(chat_page.chat_text, 1, wx.EXPAND | wx.ALL, 5)

        chat_page.message_text = wx.TextCtrl(chat_page)
        chat_sizer.Add(chat_page.message_text, 0, wx.EXPAND | wx.ALL, 5)

        send_button = wx.Button(chat_page, label="Send")
        send_button.Bind(wx.EVT_BUTTON, self.on_send)
        chat_sizer.Add(send_button, 0, wx.ALL, 5)

        chat_page.SetSizer(chat_sizer)
        return chat_page

    def on_page_changed(self, event):
        old_page = event.GetOldSelection()
        new_page = event.GetSelection()
        contact_name = self.listbook.GetPageText(new_page)

        self.GetSizer().Replace(self.chat_pages[self.listbook.GetPageText(old_page)], self.chat_pages[contact_name])
        self.Layout()

    def on_send(self, event):
        current_page_index = self.listbook.GetSelection()
        current_page_name = self.listbook.GetPageText(current_page_index)
        current_chat_page = self.chat_pages[current_page_name]

        message = current_chat_page.message_text.GetValue()
        current_chat_page.chat_text.AppendText(f"You: {message}\n")
        current_chat_page.message_text.Clear()


class MainFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, title='Main Frame')
        panel = ChatPanel(self)
        panel.add_contact("Contact 1")  # 添加一个联系人
        self.Show()


if __name__ == "__main__":
    app = wx.App(False)
    frame = MainFrame()
    app.MainLoop()
