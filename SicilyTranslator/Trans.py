import BingDict
import BingTranslate as TranslatePkg


def Dict(word):
    data = BingDict.BingDict(word)
    res = ''
    for (attr,means) in data:
        res += attr + ' ' + means + '\n'
    return res


def Translate(text):
    return TranslatePkg.Translate(text)
