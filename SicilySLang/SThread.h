#ifndef STHREAD_H
#define STHREAD_H

#include <QThread>

#include "BigInt.h"
#include "SBuild.h"
#include "SVM.h"

//通过多线程执行SLang
class SThread : public QThread{
    Q_OBJECT
public:
    SThread();
    ~SThread();
    void Eval(string &script);
protected:
    void run();
private:
    volatile int startTime;
    SExp *e;
    streamx ss;
    stringstream mes;//结果
public:
    bool overtime();//超时
    string GetRes();
    volatile bool finished;
};

#endif // STHREAD_H
