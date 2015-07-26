#-*- coding:utf-8 -*-

import BingDict

def Dict(word):
    return 'haha'
    data = BingDict.BingDict(word)
    #list(attr,means)
    res = ''
    for (attr,means) in data:
        res += attr + ' ' + means + '\n'
    return res.encode('utf-8')
