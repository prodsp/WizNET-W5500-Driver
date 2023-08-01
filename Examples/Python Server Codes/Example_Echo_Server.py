from base64 import encode
from webbrowser import get

'''
The Echo server below sends back the received character to the client
'''

import socket

HOST = "192.168.0.110"  # The server's IP address
PORT = 15400  # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()

    print("Start")
    conn, addr = s.accept()
    print(f"Connected by {addr}")

    with conn:
        end = 0
        while(not end):
            data = conn.recv(16*1024)
            print("\nThe received data: ", data.decode(),"\n")
            conn.send(data)
