#include <QApplication>
#include <QtNetwork>
#include <QClipboard>
#include <QFileDialog>
#include <QString>
#include <algorithm>
using namespace std;

#include "MultiSLang.h"
MultiSLang MSL;

void SicilyToy::Play(){
    //Sicily教你算算术！
    string res(MSL.GetRes());
    if (res.size() > 0){
        Send(res,5);
        return;
    }
    QClipboard *clipboard = QApplication::clipboard();
    string cstr = clipboard->text().toStdString();

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);//使用这个才能使用剪贴板！
    SicilyToy toy;
    srand(size_t(time(0)));

    SVM::Init();
    SVM::AddPath(GetStdFileDir("SLang\\"));

    return a.exec();
}
