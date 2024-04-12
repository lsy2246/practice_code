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

    def sign_account(self, Id: int, password):
        if self.database_state:
            try:
                self.database_cursor.execute(f"select Id,Password from Account where Id = {Id}")
                return 0
            except pymssql as a:
                self.database_state = False
                print(a)
                return 1

