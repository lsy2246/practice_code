import os

import pymssql
import threading
import time
from .Process_Client import *


class database(ProcessClient):
    def __init__(self):
        ProcessClient.__init__(self)
        self.database_server = 'localhost'
        self.database_user = 'Chat'
        self.database_password = '123456'
        self.database_port = 8972
        self.database_name = 'Chat'
        self.database_state = False
        self.database_conn = None
        self.database_cursor = None

        current_file_path = __file__
        current_file_name = os.path.basename(current_file_path).split('.')[0]
        self.Process_client_send("Server", "Name", current_file_name)

        self.link_database_thread = threading.Thread(target=self.link_database)
        self.link_database_thread.start()

        # 创建一个互斥锁对象
        self.lock = threading.Lock()

    def link_database(self):
        while not self.database_state:
            time.sleep(1)
            try:
                self.database_conn = pymssql.connect(server=self.database_server,
                                                     user=self.database_user,
                                                     password=self.database_password,
                                                     port=self.database_port,
                                                     database=self.database_name)
                self.database_cursor = self.database_conn.cursor()
                self.database_state = True
            except pymssql.Error as a:
                print(a)

    def check_account_state(self, client_id, Id: int, password):
        if self.database_state:
            try:
                state = 2
                self.database_cursor.execute(f"select Id,Password from Account where Id = {Id}")
                request_data = self.database_cursor.fetchall()
                if len(request_data) != 0:
                    if request_data[0][1] == password:
                        state = 0
                    else:
                        state = 1

                content = {"account": Id, "status": state}
                data = {"client_id": client_id, "target": "客户端", "genre": "登录", "data": content}
                self.Process_client_send('Session_client', 'send_client', data)

            except pymssql as a:
                self.database_state = False
                print(a)

    def sign_account(self, client_id, NetName, Password):
        if self.database_state:
            # 获取锁
            self.lock.acquire()
            try:
                self.database_cursor.execute("insert into Account(NetName, Password)"
                                             f"values ('{NetName}','{Password}')")
                self.database_conn.commit()
                self.database_cursor.execute(f"SELECT SCOPE_IDENTITY() AS LastInsertedId;")
                Id = self.database_cursor.fetchone()[0]
                # 释放锁
                self.lock.release()
                info = {"Id": int(Id), "NetName": NetName, "Password": Password}

                content = {"client_id": client_id, "target": "客户端", "genre": "注册", "data": info}
                self.Process_client_send('Session_client', 'send_client', content)

            except pymssql as a:
                self.lock.release()
                self.database_state = False
                return False

    def alter_state_database(self, Id: int, sate):
        if self.database_state:
            try:
                self.database_cursor.execute(f"update Account set State = N'{sate}' where Id = {Id}")
                self.database_conn.commit()
            except pymssql as a:
                self.database_state = False
                print(a)

    def detection_data(self, Id, date):
        datas = []

        self.database_cursor.execute(f"select Id,Password,NetName,UpDataTime from Account where Id = {Id}")
        Account_database = self.database_cursor.fetchall()
        Account_content = {'Id': Account_database[0][0],
                           'Password': Account_database[0][1],
                           'NetName': Account_database[0][2],
                           'UpDataTime': Account_database[0][3].strftime('%Y-%m-%d %H:%M:%S')}
        if Account_content['UpDataTime'] == date:
            content = {"client_id": Id, "target": "客户端", "genre": "数据更新", "data": {"更新完成": Id}}
            self.Process_client_send('Session_client', 'send_client', content)
            return

        Account_data = {"Account": Account_content}
        datas.append(Account_data)

        self.database_cursor.execute(
            f"select ContactsId,Remark,State,UpDataTime from Contacts where UserId = {Id} and UpDataTime > '{date}'")
        Contacts_database = self.database_cursor.fetchall()
        for Contact in Contacts_database:
            Contacts_content = {'Contact': Contact[0],
                                'Remark': Contact[1],
                                'State': Contact[2],
                                'UpDataTime': Contact[3].strftime('%Y-%m-%d %H:%M:%S')}
            Contacts_data = {"Contacts": Contacts_content}
            datas.append(Contacts_data)

        self.database_cursor.execute(f"select * from History where Send = {Id} or Receive = {Id} and Time > '{date}'")
        History_database = self.database_cursor.fetchall()
        for History in History_database:
            content = {
                'Send': History[0],
                'Receive': History[1],
                'Type': History[2],
                'Content': History[3],
                'Time': History[4].strftime('%Y-%m-%d %H:%M:%S')}
            History_data = {"History": content}
            datas.append(History_data)

        datas.append({"更新完成": Id})

        for data in datas:
            time.sleep(0.1)
            content = {"client_id": Id, "target": "客户端", "genre": "数据更新", "data": data}
            self.Process_client_send('Session_client', 'send_client', content)

    def update_History(self, Send, Receive, Type, Content, Time):
        if self.database_state:
            try:
                self.database_cursor.execute(f"insert into History(Send, Receive, Type, Content,Time)"
                                             f"select {Send},{Receive},'{Type}',N'{Content}','{Time}'")
                self.database_conn.commit()
            except pymssql as a:
                self.database_state = False
                print(a)

    def Process_client_pick(self, data):
        if data['target'] in ['ALL', 'Database_formula']:
            match data['function']:
                case 'check_account_state':

                    self.check_account_state(data['content']['client_id'],
                                             data['content']['account'],
                                             data['content']['password'])

                case 'sign_account':

                    self.sign_account(data['content']['client_id'],
                                      data['content']['account'],
                                      data['content']['password'])

                case 'alter_state_database':
                    self.alter_state_database(data['content']['Id'],
                                              data['content']['sate'])

                case 'detection_data':
                    self.detection_data(data['content']['client_id'],
                                        data['content']['date'])

                case 'update_History':
                    self.update_History(data['content']['Send'],
                                        data['content']['Receive'],
                                        data['content']['Type'],
                                        data['content']['Content'],
                                        data['content']['Time'])
