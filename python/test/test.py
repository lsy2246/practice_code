# 服务端
import socket
import cv2
import pickle
import struct

HOST = '127.0.0.1'  # 服务器IP地址
PORT = 65432        # 监听端口

# 创建Socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen(5)

# 接受客户端连接
connection, address = server_socket.accept()
print('Connected by', address)

# 使用OpenCV捕获视频
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    # 将视频帧序列化
    data = pickle.dumps(frame)
    # 将序列化的数据封装成一个结构体
    message = struct.pack("Q", len(data)) + data
    # 发送数据到客户端
    connection.sendall(message)

# 释放资源
connection.close()
server_socket.close()
cap.release()
