from socket import socket, AF_INET, SOCK_STREAM

# AF_INET 使用Internet之间的进程进行通信
# SOCK_STRAEAM 表明使用TCP协议进行编程

# 1.创建socket对象
server_socket = socket(AF_INET, SOCK_STREAM)
# 2.绑定ip和端口
ip = "localhost"
port = 8778
server_socket.bind((ip, port))
# 使用listen()监听
server_socket.listen(5)
print("服务器已近启动")
client_socket, client_obj = server_socket.accept()  # 系列解包赋值
# 等待客户端连接
info = ""
while info != "exit":
    ##接收数据
    data = client_socket.recv(1024)
    print("客户端发送过来的数据为:", data.decode("utf-8"))  # 要求客服端发过来的是utf-8进行编码的

    ##返回数据
    client_socket.send(data)
    if data.decode("utf-8") == "exit":
        break

# 关闭服务器
client_socket.close()
