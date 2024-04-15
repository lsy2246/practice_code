# 客户端
import socket
import cv2
import pickle
import struct

HOST = '127.0.0.1'  # 服务器IP地址
PORT = 65432        # 连接端口

# 创建Socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((HOST, PORT))

# 接收数据
data = b""
payload_size = struct.calcsize("Q")
while True:
    # 从服务器接收数据
    while len(data) < payload_size:
        packet = client_socket.recv(4*10240)
        if not packet: break
        data += packet
    packed_msg_size = data[:payload_size]
    data = data[payload_size:]
    msg_size = struct.unpack("Q", packed_msg_size)[0]

    # 接收视频帧
    while len(data) < msg_size:
        data += client_socket.recv(4*1024)
    frame_data = data[:msg_size]
    data = data[msg_size:]

    # 反序列化视频帧
    frame = pickle.loads(frame_data)

    # 显示视频
    cv2.imshow('frame', frame)
    if cv2.waitKey(1) == 27:
        break

# 释放资源
client_socket.close()
cv2.destroyAllWindows()
