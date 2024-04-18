import os
import csv

from .Process_Client import ProcessClient


class FileOperate(ProcessClient):
    def __init__(self):
        ProcessClient.__init__(self)

        current_file_path = __file__
        current_file_name = os.path.basename(current_file_path).split('.')[0]
        self.Process_client_send("Server", "Name", current_file_name)

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

    def Process_client_pick(self, data):
        if data['target'] in ['ALL', 'file_operate']:
            print(data)
            #match data['function']:
