import socket

TCP_IP = "10.110.225.25"   # 本机回环
TCP_PORT = 5005        # 目标端口
BUFFER_SIZE = 1024

# 创建 TCP socket
server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_sock.bind((TCP_IP, TCP_PORT))
server_sock.listen(1)   # 允许1个客户端连接
print(f"[TCP SERVER] Listening on {TCP_IP}:{TCP_PORT}...")

conn, addr = server_sock.accept()
print(f"[TCP SERVER] Connection accepted from {addr[0]}:{addr[1]}")

while True:
    data = conn.recv(BUFFER_SIZE)
    if not data:
        print("[TCP SERVER] Connection closed by client")
        break
    print(f"[RECEIVED] {data.decode()}")
    reply = "Hello from Python"
    conn.sendall(reply.encode())

conn.close()
server_sock.close()