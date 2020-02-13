#coding=utf-8
import socket

host = 'localhost'
port = 3939
addr = (host, port)
sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
def Say(data, boxLife = 0):
    msg = data + chr(boxLife)
    sock.sendto(msg.encode('utf-8'), addr)

if __name__ == '__main__':
    Say('hello')
