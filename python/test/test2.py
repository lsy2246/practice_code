import wx
import wx.richtext as rt


class MyFrame(wx.Frame):
    def __init__(self, parent, id, title):
        wx.Frame.__init__(self, parent, id, title, size=(400, 300))
        panel = wx.Panel(self)
        vbox = wx.BoxSizer(wx.VERTICAL)

        # 创建 RichTextCtrl
        self.rtc = rt.RichTextCtrl(panel, style=wx.VSCROLL | wx.HSCROLL | wx.NO_BORDER | wx.WANTS_CHARS)
        self.rtc.BeginFontSize(12)
        self.rtc.WriteText("Here is some text, and here is an image: ")
        self.rtc.EndFontSize()

        # 插入图片
        image = wx.Bitmap('path_to_your_image.png', wx.BITMAP_TYPE_PNG)
        self.rtc.WriteImage(image)

        vbox.Add(self.rtc, 1, flag=wx.EXPAND)
        panel.SetSizer(vbox)

        self.Show()


if __name__ == '__main__':
    app = wx.App()
    MyFrame(None, -1, 'Insert Image in RichTextCtrl')
    app.MainLoop()
