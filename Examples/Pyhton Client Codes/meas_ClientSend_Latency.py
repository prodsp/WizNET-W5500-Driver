'''
The RTT latency was measured by an echo command.
'''
from base64 import encode
from webbrowser import get

'''
Use "open" command, to open a socket. The "quit" command terminates the client program.
As a data you can add any character and you will get back the given charater + 1 in ASCII.
e.g.: Enter data: a --> received data: b
If you enter "close" string as a command, the client program closes the socket.
'''

import socket
import time
import datetime
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
    for x in range(1000):
        dt1 = time.perf_counter_ns()
        print(dt1)
        datalength = s.send(prev_rec_data.encode())
        dt2 = time.perf_counter_ns()
        print(dt2)
        data = s.recv(16*1024)
        dt = dt2-dt1
        print(dt)
        print(datalength)
        csvWrite.writerow([dt1, dt2, dt])
        print("\nThe recieved data: ", data,"\n")
f.close()

        
    

