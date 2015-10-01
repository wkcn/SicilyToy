#coding=utf-8
import pyperclip
import time
import socket
import TrieTree
import Trans
import sys
reload(sys)
sys.setdefaultencoding('utf8')


tree = TrieTree.SDict()	#暂时使用Dict而不是字典树
host = 'localhost'
port = 3939
addr = (host, port)

def ReadDict(tree,path):
	#path includes \\
	si = 0
	for i in range(26):
		fileName = path + chr(ord('a') + i) + '.txt'
		try:
			file = open(fileName,'r')
			for q in file.readlines():
				#q = q.decode('utf-8')
				sp = q.split('~')
				word = sp[0]
				content = sp[1].replace('|','\n')
				tree.insert(word,content)
				si += 1
			file.close()
		except:
			pass
	print '读取' + path + '中的词条'+ str(si) + '条'
			
sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
def SicilySay(data,boxLife = 0):
	sock.sendto(data.encode('utf-8') + chr(boxLife),addr)

ReadDict(tree,'Dict\\')
ReadDict(tree,'Dict\\Plus\\')

def SicilyTranslator():
	lastclip = pyperclip.paste()
	while True:
		clip = pyperclip.paste()
		if lastclip != clip:
			res = tree.find(clip)
			if len(res) > 0:
				data = clip
				data += '\n   意思是： ≥▽≤\n'.decode('gbk')
				data += res
				SicilySay(data,5)
			else:
				#Bing
				res = Trans.Dict(clip)
				if len(res) > 0:
					data = clip
					data += '\n   意思是： ヾ(￣▽￣)\n'.decode('gbk')
					data += res
					SicilySay(data,5)
					#append
					tree.insert(clip,res)
					file = open('Dict\\Plus\\' + clip[0].lower() + '.txt','a')
					if res[-1] == '\n':
						res = res[:-1]
					file.write(clip.strip('\n') + '~' + res.replace('\n','|') + '\n')
					file.close()
					print 'Append ' + clip
				else:
					#baidu
					res = Trans.Translate(clip)
					if len(res) > 0:
						data = clip
						data += '\n   意思是： o(^_^)o \n'.decode('gbk')
						data += res
						SicilySay(data,5)
					else:
						data = '不知道啊 ≥﹏≤'.decode('gbk')
						SicilySay(data,0)
						print 'sentence'
			lastclip = clip
		time.sleep(3)
		
if __name__ == '__main__':
	SicilyTranslator()