#coding=utf-8
import pyperclip
import os
import time
import socket
import TrieTree
import Trans
import Sicily
'''
import sys
reload(sys)
sys.setdefaultencoding('utf8')
'''

tree = TrieTree.SDict()    #暂时使用Dict而不是字典树

def ReadDict(tree,path):
    #path includes \\
    si = 0
    for i in range(26):
        fileName = path + chr(ord('a') + i) + '.txt'
        if os.path.exists(fileName):
            with open(fileName, 'r', encoding='utf-8') as fin:
                for q in fin.readlines():
                    sp = q.split('~')
                    word = sp[0]
                    content = sp[1].replace('|','\n')
                    tree.insert(word,content)
                    si += 1
    print ('读取' + path + '中的词条'+ str(si) + '条')
            

DICT_PLUS_DIRNAME = 'Dict/Plus/'
if not os.path.exists(DICT_PLUS_DIRNAME):
    os.makedirs(DICT_PLUS_DIRNAME)
ReadDict(tree, 'Dict/')
ReadDict(tree, DICT_PLUS_DIRNAME)

def SicilyTranslator():
    lastclip = pyperclip.paste()
    while True:
        try:
            clip = pyperclip.paste()
            if lastclip != clip:
                res = tree.find(clip)
                if len(res) > 0:
                    data = clip
                    data += '\n   意思是： ≥▽≤\n'
                    data += res
                    Sicily.Say(data,5)
                else:
                    #Bing
                    res = Trans.Dict(clip)
                    if len(res) > 0:
                        data = clip
                        data += '\n   意思是： ヾ(￣▽￣)\n'
                        data += res
                        Sicily.Say(data,5)
                        #append
                        tree.insert(clip,res)
                        na = clip[0].lower()
                        if na >= 'a' and na <= 'z':
                            with open('Dict/Plus/' + na + '.txt','a', encoding='utf-8') as fout:
                                if res[-1] == '\n':
                                    res = res[:-1]
                                fout.write(clip.strip('\n') + '~' + res.replace('\n','|') + '\n')
                            print ('Append ' + clip)
                    else:
                        #baidu
                        res = Trans.Translate(clip)
                        if len(res) > 0:
                            data = clip
                            data += '\n   意思是： o(^_^)o \n'
                            data += res
                            Sicily.Say(data,5)
                        else:
                            data = '不知道啊 ≥﹏≤'
                            Sicily.Say(data,0)
                            print ('sentence')
                lastclip = clip
        except BaseException as e:
            raise
            print (e)
        time.sleep(1)
        
if __name__ == '__main__':
    SicilyTranslator()
