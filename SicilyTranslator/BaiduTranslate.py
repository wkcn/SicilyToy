#-*- coding:utf-8 -*-

import urllib,urllib2
import cookielib
import gzip
import StringIO
import json
from bs4 import BeautifulSoup

cookie = cookielib.CookieJar()
opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cookie))

def GetHTML(text):
    try:
        BaiduAPIKey = ''
        import SicilyConfig
        BaiduAPIKey = SicilyConfig.BaiduAPIKey
    except ImportError:
        pass

    params = {'from':'auto',\
              'to':'auto',\
              'client_id':BaiduAPIKey,\
              'q':text
            }

    paramsCode = urllib.urlencode(params)
    url = 'http://openapi.baidu.com/public/2.0/bmt/translate?' + paramsCode

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
    except:
        return ''


#print Translate("how are you\ntoday is a good day")
