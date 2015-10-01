#include "SThread.h"

SThread::SThread(){
    e = 0;
}

SThread::~SThread(){
    if (!e)DelSExp(e);
}

void SThread::Eval(string &script){
    ss << script;
    //mes << script << endl;
    if (script[0] == '#'){
        mes << script.substr(1);
    }else{
        mes << script;
    }
    mes << endl;
    startTime = time(0);
    finished = false;
    //qDebug("%s=-=-",script.c_str());
    start();
}

string SThread::GetRes(){
    return mes.str();
}

void SThread::run(){
    SBuild bu;
    bu.SetStream(ss);
    SVM vm;
    vm.SetVar("x", Poly(1, 1));
    e = bu.Build();
    Poly value = vm.Eval(e);
    mes << "   的结果是：" << endl;
    mes << value;
    //cout << value << endl;
    //Send(mes.str(),sender);
    DelSExp(e);
    e = 0;
    //mes.str("");
    finished = true;
    //qDebug("okok%s",mes.str().c_str());
}

bool SThread::overtime(){
    return (time(0) - startTime) > 10;
}
