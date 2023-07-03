'''
The Data Loss was measured by an echo command.
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


        
    

