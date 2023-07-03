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

SERV_IP = "192.168.0.22"  # The server's hostname or IP address
SERV_PORT = 15200  # The port used by the server

command = input("\nCommand:")

while command != "quit" and command != "QUIT":
    if command == "open" or command == "OPEN":    
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((SERV_IP, SERV_PORT))
            print("Connected!")
            onemore = input("\nEnter data: ")
            prev_rec_data = onemore
            while onemore!="close" and onemore != "CLOSE":
                s.send(prev_rec_data.encode())
                data = s.recv(16*1024)
                print("\nThe sent data:", prev_rec_data,)
                print("\nThe recieved data: ", data,"\n")
                onemore = input("\nEnter data: ")
                if onemore == "close" or onemore == "CLOSE":
                    s.close
                    print("\nSocket Closed!")
                prev_rec_data = onemore
    command = input("\nCommand:")

        
    

