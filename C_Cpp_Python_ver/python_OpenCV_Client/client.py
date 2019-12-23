#-*- coding:utf-8 -*-
import socket 

HOST = '192.168.8.177'
PORT = 8080

def unlock(name):
    client_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM) 
    client_socket.connect((HOST, PORT))
    client_socket.send(name.encode()) 
    data = client_socket.recv(1024) 
    client_socket.close() 
    

