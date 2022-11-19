#-*- coding:utf-8 -*-

import urllib
import gzip
from io import BytesIO
import json
from hashlib import md5
from SicilyConfig import *
from bs4 import BeautifulSoup

def GetHTML(text, src='auto', dst='auto'):
    idd = BAIDU_APPID + text + '0' + BAIDU_KEY
    m1 = md5()
    m1.update(idd.encode('utf-8'))
    md5res = m1.hexdigest()

    params = {'from': src,
              'to': dst,
              'q': text,
              'appid': BAIDU_APPID,
              'salt': '0',
              'sign': md5res
            }

    paramsCode = urllib.parse.urlencode(params)
    url = 'http://api.fanyi.baidu.com/api/trans/vip/translate?' + paramsCode
    print(url)

    req = urllib.request.Request(url)
    resp = urllib.request.urlopen(req)
    return resp.read()


def Translate(text, src='auto', dst='auto'):
    try:
        html = GetHTML(text, src=src, dst=dst)
        res = []
        print(html)
        for s in json.loads(html)['trans_result']:
            res.append(s['dst'])
        return '\n'.join(res)
    except BaseException as e:
        # print(e, json.loads(html))
        raise


if __name__ == '__main__':
    res = Translate("how are you\ntoday is a good day")
    print(res, type(res))
