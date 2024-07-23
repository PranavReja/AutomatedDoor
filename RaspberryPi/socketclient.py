# client.py

#importing socket module
import socket

# creating socket instance
client_object = socket.socket(family=socket.AF_INET, type=socket.SOCK_STREAM)

# target ip address and port
ip_address = '10.0.0.221'
port = 8000

# instance requesting for connection to the specified address and port
client_object.connect((ip_address,port))

# receiving response from server

client_input = "face".encode('utf-8')
        
client_object.send(client_input)

