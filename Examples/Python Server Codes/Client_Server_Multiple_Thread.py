from base64 import encode
from webbrowser import get

'''
This example consist from a Server and a Client part

Server:
Receives a number from the WizNET (client), checks if it is in the given range, and sends back a validation message.

Client:
Sends the user given number to the WizNET (server), and receives the data length calculated by the server and a validation message.


Use W5500_Client_Server_Multiple_Thread.c
'''

import socket
import threading

PY_SERV_IP = "192.168.0.110"  # The python server's IP address
PY_SERV_PORT = 15400  # The port used by the python server
WIZNET_SERV_IP = "192.168.0.22" # The WizNET server's IP address
WIZNET_SERV_PORT = 15200 # The port used by the WizNET server

#--------------------------------------------- Server --------------------------------------------
def socket0():
    MIN = 100
    MAX = 1000000000
    global socket0_connected
    socket0_connected = False

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s0:
        s0.bind((PY_SERV_IP, PY_SERV_PORT))
        s0.listen()

        print("Server -- Waiting for client connection!\n")
        conn, addr = s0.accept()
        print(f"Server -- Connected by {addr}","\n")
        socket0_connected = True

        with conn:
            end = 0
            while(not end):
                data = conn.recv(8*1024)
                print("Server -- The received data: ", data.decode(),"\n")
                if ((int(data) < MIN) or (int(data) > MAX)):
                    send_data = "Number is not in range!\n"
                else:
                    send_data = "Number is in range!\n"
                conn.send(send_data.encode())

#--------------------------------------------- Client ---------------------------------------------
def socket1():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s1:
        s1.connect((WIZNET_SERV_IP, WIZNET_SERV_PORT))
        print("Client -- Connected to WizNET server!\n")

        end = 0
        while(not end):
            while not socket0_connected:
                continue
            send_data = input("Client -- Give me a number: ")
            s1.send(send_data.encode())
            data = s1.recv(8*1024)
            print("\nClient -- Data length is ", data.decode(),"byte\n")

            data = s1.recv(8*1024)
            print("Client -- ", data.decode(), "\n")

threading.Thread(target=socket0).start()
threading.Thread(target=socket1).start()
