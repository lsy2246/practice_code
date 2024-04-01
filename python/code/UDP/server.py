from socket import socket, AF_INET, SOCK_DGRAM

# 创建socket对象
server_socket = socket(AF_INET, SOCK_DGRAM)

# 绑定ip和端口
ip = "localhost"
port = 8778
server_socket.bind((ip, port))

# 等待客户端连接
info = ""
while info != "exit":
    # 接收数据
    data, addr = server_socket.recvfrom(1024)
    print("客户端发送过来的数据为:", data.decode("utf-8"))  # 要求客户端发过来的是utf-8进行编码的
    if data.decode("utf-8") == "exit":
        server_socket.sendto(data, addr)  # 回复的数据
        break

    # 返回数据
    send_data = input("请输入:")
    server_socket.sendto(send_data.encode("utf-8"), addr)  # 回复的数据

# 关闭服务器
server_socket.close()
