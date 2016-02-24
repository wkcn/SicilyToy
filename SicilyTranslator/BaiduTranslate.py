#-*- coding:utf-8 -*-

import urllib,urllib2
import cookielib
import gzip
import StringIO
import json
import md5
from SicilyConfig import *
from bs4 import BeautifulSoup

cookie = cookielib.CookieJar()
opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cookie))

def GetHTML(text):
    
    src = BAIDU_APPID + text + '0' + BAIDU_KEY
    m1 = md5.new()
    m1.update(src)
    md5res = m1.hexdigest()

    params = {'from':'auto',\
              'to':'auto',\
              'q':text,
              'appid':BAIDU_APPID,
              'salt':'0',
              'sign':md5res
            }

    paramsCode = urllib.urlencode(params)
    url = 'http://api.fanyi.baidu.com/api/trans/vip/translate?' + paramsCode

    req = urllib2.Request(url)
    resp = urllib2.urlopen(req)
    return resp.read()

def Translate(text):
    try:
        html = GetHTML(text)
        res = []
        for s in json.loads(html)['trans_result']:
            res.append(s['dst'])
        return '\n'.join(res)
    except BaseException as e:
        print e
        return ''

if __name__ == '__main__':
    print Translate("how are you\ntoday is a good day")
