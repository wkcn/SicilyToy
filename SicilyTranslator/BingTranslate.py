import translators as tss


def Translate(text, src='auto', dst='auto'):
    assert src == 'auto'
    assert dst == 'auto'
    trans_text = tss.bing(text, to_language='zh', if_use_cn_host=True)
    if trans_text == text:
        trans_text = tss.bing(text, to_language='en', if_use_cn_host=True)
    return trans_text


if __name__ == '__main__':
    content = '你好啊'
    print(Translate(content))
