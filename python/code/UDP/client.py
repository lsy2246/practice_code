from socket import socket, AF_INET, SOCK_DGRAM

client_socket = socket(AF_INET, SOCK_DGRAM)

ip = "localhost"
port = 8778
info = ""

while info != "exit":
    ##发送数据
    send_data = input("请输入:")
    client_socket.sendto(send_data.encode("utf-8"), (ip, port))

    ##接收数据
    data, addr = client_socket.recvfrom(1024)
    print("接收到的数据为:", data.decode("utf-8"))

    if data.decode("utf-8") == "exit":
        client_socket.sendto(data, addr)  # 回复的数据
        break
client_socket.close()
