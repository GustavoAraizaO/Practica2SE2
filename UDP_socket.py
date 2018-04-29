import socket
import time

UDP_IP = "192.168.0.102"
UDP_PORT = 50007
MESSAGE = []
MESSAGE_2 = []
MESSAGE_B = []
MESSAGE_2_B = []

for p in range (0,16):
    for n in range(0,256):
     MESSAGE.append(5);
     MESSAGE_2.append(10);

MESSAGE_B = bytearray (MESSAGE)
MESSAGE_2_B = bytearray (MESSAGE_2)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
while True:
    sock.sendto(MESSAGE_B, (UDP_IP, UDP_PORT))
    time.sleep(00.464399)
    sock.sendto(MESSAGE_2_B, (UDP_IP, UDP_PORT))
    time.sleep(00.464399)
