#-*- coding:utf-8 -*-

import urllib
import gzip
from io import BytesIO 
from bs4 import BeautifulSoup

def GetHTML(word):
    params = {'q':word,\
            'go':'提交',\
            'qs':'n',\
            'form':'CM',\
            'pq':word,\
            'sc':'7-5',\
            'sp':'-1',\
            'sk':''}
    paramsCode = urllib.parse.urlencode(params)
    url = 'http://cn.bing.com/dict/search?%s' % paramsCode

    headers = {'Accept':'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8',\
            'Accept-Encoding':'gzip, deflate, sdch',\
            'Accept-Language':'zh-CN,zh;q=0.8',\
            'Connection':'keep-alive',\
            'Host':'cn.bing.com',\
            'Referer':url,\
            'User-Agent':'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2272.89 Safari/537.36'}
    try:
        req = urllib.request.Request(url, headers=headers)
        resp = urllib.request.urlopen(req)
        data = BytesIO(resp.read())
        gzipper = gzip.GzipFile(fileobj = data)
        html = gzipper.read()
        return html
    except:
        return ''

def BingDict(word):
    html = GetHTML(word)
    res = []
    soup = BeautifulSoup(html,'html.parser')
    for span in soup.find_all(class_ = 'def'):
        attr = span.previous_sibling.string
        means = ''.join(span.strings)
        res.append((attr,means))
    return res


if __name__ == '__main__':
    print("===")
    for (attr, means) in BingDict('hello'):
        print (attr, means, type(attr), type(means))
