#-*- coding:utf-8 -*-

import BingDict
import BaiduTranslate

def Dict(word):
    data = BingDict.BingDict(word)
    #list(attr,means)
    res = ''
    for (attr,means) in data:
        res += attr + ' ' + means + '\n'
    return res.encode('utf-8')

def Translate(text):
    return BaiduTranslate.Translate(text).encode('utf-8')
