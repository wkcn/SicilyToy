#include "MultiSLang.h"

MultiSLang::MultiSLang(){
}

MultiSLang::~MultiSLang(){
    for(auto iter = ts.begin();iter!=ts.end();++iter){
        delete *iter;
    }
}

void MultiSLang::Eval(string &word){
    SThread *t = new SThread;
    t->Eval(word);
    ts.push_back(t);
}

string MultiSLang::GetRes(){
    //(*iter)返回的是SThread指针
    for(auto iter = ts.begin();iter!=ts.end();++iter){
        if ((*iter)->overtime()){
            //qDebug("over");
            delete *iter;
            ts.erase(iter);
            continue;
        }
        if ((*iter)->finished){
            string res = (*iter)->GetRes();
            //qDebug("%s--",res.c_str());
            delete *iter;
            ts.erase(iter);
            return res;
        }
    }
    return "";
}
