#coding=utf-8
import socket

host = 'localhost'
port = 3939
addr = (host, port)
sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
def Say(data,boxLife = 0):
    sock.sendto(data + chr(boxLife),addr)

if __name__ == '__main__':
    Say('hello')
