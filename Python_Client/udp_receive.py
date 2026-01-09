import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(("10.110.225.25", 5005))
print("Listening UDP 5005...")
while True:
    data, addr = s.recvfrom(1024)
    print("Received:", data, "from", addr)