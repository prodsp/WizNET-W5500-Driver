'''
Use W5500_Example_Echo_Server.c
'''

from base64 import encode
from webbrowser import get

import socket
import time
import csv

SERV_IP = "192.168.0.22"  # The server's hostname or IP address
SERV_PORT = 15200  # The port used by the server

f = open("C:/Users/MateKocsis/Downloads/latency.csv", 'w', newline='')
csvWrite = csv.writer(f)
  
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((SERV_IP, SERV_PORT))
    print("Connected!")
    prev_rec_data = ''
    for i in range(1000):
        prev_rec_data += 'a'
    for x in range(10000):
        dt1 = round(time.time()*1000000)
        print(dt1)
        s.send(prev_rec_data.encode())
        data = s.recv(16*1024)
        dt2 = round(time.time()*1000000)
        print(dt2)
        dt = dt2-dt1
        csvWrite.writerow([dt1, dt2, dt])
        print("\nThe recieved data: ", data,"\n")
f.close()

        
    

