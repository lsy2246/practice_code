from socket import socket, AF_INET, SOCK_STREAM

client_socket = socket(AF_INET, SOCK_STREAM)

ip = "localhost"
port = 8778
client_socket.connect((ip, port))
info = ""

while info != "exit":
    send_data = input("请输入:")
    client_socket.send(send_data.encode("utf-8"))

    if send_data == "exit":
        break
    info = client_socket.recv(1024).decode("utf-8")
    print("收到服务端响应数据:", info)
client_socket.close()
