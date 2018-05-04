import wave
from scipy.io import wavfile
import socket
import numpy
import time

UDP_IP = "192.168.0.102"
UDP_PORT = 50009

fs, data = wavfile.read("C:\Look_what_you_made_me_do.wav")
data_to_send = data[:,0]
data_to_send.setflags(write=1)
pkg_size = 4096

for n in range(0,len(data_to_send)):
    if data_to_send[n] <= -1:
        data_to_send[n] = -0.9999
    if data_to_send[n] >= 1:
        data_to_send[n] = 0.9999

data_to_send = (data_to_send + 1) * (2**11)

data_to_bytes = []
data_int = []
data_break = []

for n in range (0,int(len(data_to_send)/2)):
    data_int.append(int(data_to_send[n*2]))
for n in range (0,len(data_int)):
    data_break.append(data_int[n]&0xFF)
    data_break.append((data_int[n]>>8)&0xFF)
data_to_bytes = bytearray(data_break)

n = 0

while True:
    tic = time.clock()
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    if n > len(data_to_bytes):
        n = 0
    sock.sendto(data_to_bytes[n:n + (pkg_size - 1)], (UDP_IP, UDP_PORT))
    n = n + pkg_size
    toc = time.clock()
    time.sleep(0.092879 - (tic - toc))
    #time.sleep(0.009029 - (tic - toc))