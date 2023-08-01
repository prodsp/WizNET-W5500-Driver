'''
Use W5500_Measure_Data_Loss.c or W5500_example_Counter.c
'''

from base64 import encode
from webbrowser import get

import socket

SERV_IP = "192.168.0.22"  # The server's hostname or IP address
SERV_PORT = 15200  # The port used by the server

counter = 1
  
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((SERV_IP, SERV_PORT))
    print("Connected!")
    prev_rec_data = 'a'
    while 1:
        datasie = s.send(prev_rec_data.encode())
        data = s.recv(8)
        print("S:", int.from_bytes(data,'big'), " --> ", "C:", counter)
        counter = counter+1


        
    

