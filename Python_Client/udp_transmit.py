import socket
import time

# Python 发送端
UDP_IP = "10.110.225.25"    # 回环测试，本机 IP
UDP_PORT = 49672             # 目标端口
INTERVAL = 1                # 周期发送间隔 (秒)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

count = 0
while True:
    msg = f"Python UDP Packet #{count}"
    sock.sendto(msg.encode(), (UDP_IP, UDP_PORT))
    print(f"[SENT] {msg} -> {UDP_IP}:{UDP_PORT}")
    count += 1
    time.sleep(INTERVAL)