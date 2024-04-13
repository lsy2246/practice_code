import pymssql
import threading
import time


class database:
    def __init__(self):
        self.database_server = 'localhost'
        self.database_user = 'Chat'
        self.database_password = '123456'
        self.database_port = 8972
        self.database_name = 'Chat'
        self.database_state = False
        self.database_conn = None
        self.database_cursor = None

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

    def check_account_state(self, Id: int, password):
        if self.database_state:
            try:
                self.database_cursor.execute(f"select Id,Password from Account where Id = {Id}")
                request_data = self.database_cursor.fetchall()
                if len(request_data) != 0:
                    if request_data[0][1] == password:
                        return 0
                    else:
                        return 1
                else:
                    return 2
            except pymssql as a:
                self.database_state = False
                print(a)

    def sign_account(self, NetName, Password):
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
                return {"Id": int(Id), "NetName": NetName, "Password": Password}
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
