#-*- coding:utf-8 -*-

import BingDict
import BaiduTranslate
#import goslate

def Dict(word):
    data = BingDict.BingDict(word)
    #list(attr,means)
    res = ''
    for (attr,means) in data:
        res += attr + ' ' + means + '\n'
    return res

#gs = goslate.Goslate()
def Translate(text):
    return BaiduTranslate.Translate(text)
'''
    try:
        return gs.translate(text,'zh')
    except BaseException as e:
        print e
        return ''
'''
