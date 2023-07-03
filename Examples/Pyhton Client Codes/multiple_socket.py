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
import threading

SERV_IP = "192.168.0.22"  # The server's hostname or IP address
SERV_PORT0 = 15200  # The port used by the server
SERV_PORT1 = 16200

def socket0():
    counter0 = 1
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s0:
        s0.connect((SERV_IP, SERV_PORT0))
        print("Connected! --> 0")
        prev_rec_data0 = 'a'
        while 1:
            time.sleep(1)
            s0.send(prev_rec_data0.encode())
            data0 = s0.recv(8)
            print("S0:", int.from_bytes(data0,'big'), " --> ", "C0:", counter0)
            counter0 = counter0+1

def socket1():
    counter1 = 1
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s1:
        s1.connect((SERV_IP, SERV_PORT1))
        print("Connected! --> 1")
        prev_rec_data1 = 'a'
        while 1:
            time.sleep(0.5)
            s1.send(prev_rec_data1.encode())
            data1 = s1.recv(8)
            print("S1:", int.from_bytes(data1,'big'), " --> ", "C1:", counter1)
            counter1 = counter1+1


threading.Thread(target=socket0).start()
threading.Thread(target=socket1).start()














