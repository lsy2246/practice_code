import os
import csv
import time

from .Process_Client import ProcessClient


class FileOperate(ProcessClient):
    def __init__(self, user_id):
        ProcessClient.__init__(self)

        self.user_id = user_id

        self.root_path = None
        self.Account_path = None
        self.Contacts_path = None
        self.History_path = None
        self.file_root_path = None
        self.other_file_path = None
        self.image_file_path = None

        current_file_path = __file__
        current_file_name = os.path.basename(current_file_path).split('.')[0]
        self.Process_client_send("Server", "Name", current_file_name)

    def detection_data(self, Id):
        self.user_id = Id
        self.root_path = rf'.\{Id}'
        self.Account_path = self.root_path + r'\Account.csv'
        self.Contacts_path = self.root_path + r'\Contacts.csv'
        self.History_path = self.root_path + r'\History.csv'
        self.file_root_path = self.root_path + r'\file'
        self.other_file_path = self.file_root_path + r'\other'
        self.image_file_path = self.file_root_path + r'\image'
        if not os.path.isdir(self.root_path):
            os.mkdir(self.root_path)
        if not os.path.isdir(self.file_root_path):
            os.mkdir(self.file_root_path)
            os.mkdir(self.other_file_path)
            os.mkdir(self.image_file_path)
        if not os.path.exists(self.Account_path):
            with open(self.Account_path, 'w', encoding='utf-8') as f:
                pass
        with open(self.Account_path, 'r+', encoding='utf-8') as info:
            data = csv.DictReader(info)
            if os.path.getsize(self.Account_path) == 0:  # 检查文件大小是否为0
                date = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(0))
            else:
                for d in data:
                    date = d['UpDataTime']

            target = "服务器"
            genre = "数据更新"
            data = {"genre": genre, "target": target, "content": date}
            self.Process_client_send("Session_server", "send_server", data)

    def read_data(self):
        with open(self.Contacts_path, 'r', encoding='utf-8') as Contacts:
            data = csv.reader(Contacts)
            next(data)
            for i in data:
                content = {'Contact': i[0], 'Remark': i[1], 'state': i[2], 'UpDataTime': i[3]}
                self.Process_client_send("Chat_main", "ChatPage_add_Contact_person", content)
        with open(self.History_path, 'r', encoding='utf-8') as History_path:
            data = csv.reader(History_path)
            next(data)
            for i in data:
                content = {'send': i[0], 'receive': i[1], 'Type': i[2], 'content': i[3], 'UpDataTime': i[4]}
                self.Process_client_send("Chat_main", "ChatPage_add_Contact_tab", content)

    def save_data(self, data):
        target = list(data.keys())[0]
        data = list(data.values())[0]
        match target:
            case 'Account':
                with open(self.Account_path, 'w+', encoding='utf-8', newline='') as file:
                    csv_file = csv.writer(file)
                    csv_file.writerow(list(data.keys()))
                    csv_file.writerow(list(data.values()))
            case 'Contacts':
                with open(self.Contacts_path, 'a+', encoding='utf-8', newline='') as file:
                    csv_file = csv.writer(file)
                    if os.path.getsize(self.Contacts_path) == 0:  # 检查文件大小是否为0
                        csv_file.writerow(list(data.keys()))
                    csv_file.writerow(list(data.values()))
            case 'History':
                with open(self.History_path, 'a+', encoding='utf-8', newline='') as file:
                    csv_file = csv.writer(file)
                    if os.path.getsize(self.History_path) == 0:  # 检查文件大小是否为0
                        csv_file.writerow(list(data.keys()))
                    csv_file.writerow(list(data.values()))
            case '更新完成':
                self.Process_client_send("ALL", "更新完成", eval(data))

    def Process_client_pick(self, data):
        if data['target'] in ['ALL', 'File_operate']:
            match data['function']:
                case 'detection_data':
                    self.detection_data(data['content'])
                case 'save_data':
                    self.save_data(data['content'])
                case 'read_data':
                    self.read_data()
