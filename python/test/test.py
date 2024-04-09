import wx,time
ID_EXIT=200
ID_ABOUT=201

class Frame(wx.Frame): #2 wx.Frame子类
    def __init__(self,parent = None,id = -1,title ='系统管理界面'):
        wx.Frame.__init__(self,parent,id,title,size=(900,600))
        self.panel_Celan1 = None
        self.panel_Celan2 = None
        self.panel_Celan3 = None
        self.panel_Celan1_1 =None
        self.setupStatusBar()
        self.InitCelan()
        self.InitButton()


    #初始化状态栏
    def setupStatusBar(self):
        # 状态栏
        sb = self.CreateStatusBar(2)  # 2代表将状态栏分为两个
        self.SetStatusWidths([-1, -2])  # 比例为1：2
        self.SetStatusText("Ready", 0)  # 0代表第一个栏，Ready为内容
        # timmer
        self.timer = wx.PyTimer(self.Notify)
        self.timer.Start(1000, wx.TIMER_CONTINUOUS)
        self.Notify()

    # 实时显示时间
    def Notify(self):
        t = time.localtime(time.time())
        st = time.strftime('%Y-%m-%d %H:%M:%S', t)
        self.SetStatusText(st, 1)  # 这里的1代表将时间放入状态栏的第二部分上


    # 初始化登陆
    def InitButton(self):
        self.panel_Celan1 = wx.Panel(self, pos=(400, 150), size=(300, 300))
        wx.StaticText(self.panel_Celan1,label="Username",pos=(20,20))
        wx.StaticText(self.panel_Celan1, label="Password", pos=(20, 50))
        self._username=wx.TextCtrl(self.panel_Celan1,pos=(110,15))
        self._passwd = wx.TextCtrl(self.panel_Celan1, pos=(110, 45),style=wx.TE_PASSWORD)

        self._submit_btn=wx.Button(self.panel_Celan1,label=u'提交',pos=(100,100),size=(50,30))
        self.panel_Celan1.Bind(wx.EVT_BUTTON,self.Onclick,self._submit_btn)


    #处理登陆事件
    def Onclick(self,event):
        global denglu_flag
        if event.GetEventObject()==self._submit_btn:
            user = self.GetUsername()
            passwd = self.GetPasswd()
            print(user+":"+passwd)
            if(user == "wenli"and passwd == "123456"):
                denglu_flag=True
                self.panel_Celan1.Destroy()
                self.panel_Celan1_1 =wx.Panel(self, pos=(400, 150), size=(300, 300))
                wx.StaticText(self.panel_Celan1_1, label="欢迎登陆", pos=(130, 150))
    def GetUsername(self):
        return self._username.GetValue()

    def GetPasswd(self):
        return self._passwd.GetValue()



    #处理侧栏的点击事件
    def Onclick_Ce(self,event):
        global denglu_flag
        if event.GetEventObject() == self._caidan1:
            # 如果需要显示的地方存在其他面板，删除
            if self.panel_Celan2:
                 self.panel_Celan2.Destroy()
            if self.panel_Celan3:
                self.panel_Celan3.Destroy()
            if not self.panel_Celan1 :
                if(denglu_flag == False):
                    self.InitButton()
                else:
                    if not self.panel_Celan1_1:
                        self.panel_Celan1_1 = wx.Panel(self, pos=(400, 150), size=(300, 300))
                        wx.StaticText(self.panel_Celan1_1, label="欢迎登陆", pos=(130, 150))


        if event.GetEventObject()==self._caidan2:
            # 如果需要显示的地方存在其他面板，删除
            if self.panel_Celan1:
                self.panel_Celan1.Destroy()
            if self.panel_Celan1_1:
                self.panel_Celan1_1.Destroy()
            if self.panel_Celan3:
                self.panel_Celan3.Destroy()
            if not self.panel_Celan2 :
                self.panel_Celan2 = wx.Panel(self, pos=(200, 0), size=(700, 700))

        if event.GetEventObject() == self._caidan3:
            if self.panel_Celan1:
                self.panel_Celan1.Destroy()
            if self.panel_Celan1_1:
                self.panel_Celan1_1.Destroy()
            if  self.panel_Celan2 :
                self.panel_Celan2.Destroy()
            if not self.panel_Celan3:
                self.panel_Celan3 = wx.Panel(self, pos=(400, 150), size=(300, 300))
                wx.StaticText(self.panel_Celan3, label="公告", pos=(130, 150))


class App(wx.App): #5 wx.App子类
    def __init__(self):
    #如果要重写__init__,必须调用wx.App的__init__,否则OnInit方法不会被调用
        wx.App.__init__(self)
    def OnInit(self):
        self.frame=Frame()
        self.SetTopWindow(self.frame)
        self.frame.Show()

        return True
if __name__=="__main__":
    denglu_flag = False
    app = App()
    app.MainLoop()