#ifndef MULTISLANG_H
#define MULTISLANG_H

#include "SThread.h"
#include <list>
using namespace std;

class MultiSLang{
public:
    void Eval(string &word);//执行
    string GetRes();//获得输出
    MultiSLang();
    ~MultiSLang();
private:
    list<SThread*> ts;
};

#endif // MULTISLANG_H
