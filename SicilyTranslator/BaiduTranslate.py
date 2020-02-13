#-*- coding:utf-8 -*-

import urllib
import gzip
from io import BytesIO
import json
from hashlib import md5
from SicilyConfig import *
from bs4 import BeautifulSoup

def GetHTML(text):
    
    src = BAIDU_APPID + text + '0' + BAIDU_KEY
    m1 = md5()
    m1.update(src.encode('utf-8'))
    md5res = m1.hexdigest()

    params = {'from':'auto',\
              'to':'auto',\
              'q':text,
              'appid':BAIDU_APPID,
              'salt':'0',
              'sign':md5res
            }

    paramsCode = urllib.parse.urlencode(params)
    url = 'http://api.fanyi.baidu.com/api/trans/vip/translate?' + paramsCode

    req = urllib.request.Request(url)
    resp = urllib.request.urlopen(req)
    return resp.read()

def Translate(text):
    try:
        html = GetHTML(text)
        res = []
        for s in json.loads(html)['trans_result']:
            res.append(s['dst'])
        return '\n'.join(res)
    except BaseException as e:
        raise
        return ''

if __name__ == '__main__':
    res = Translate("how are you\ntoday is a good day")
    print(res, type(res))
