#include <QApplication>
#include <QtNetwork>
#include <QClipboard>
#include <QFileDialog>
#include <QString>

#include <algorithm>
using namespace std;

#include "MultiSLang.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);//使用这个才能使用剪贴板！

    srand(size_t(time(0)));

    SVM::Init();
    SVM::AddPath(GetStdFileDir("SLang\\"));

    //qDebug("%s",GetStdFileDir("SLang\\").c_str());

    MultiSLang MSL;

    //cout.rdbuf(mes.rdbuf());//重定向有乱码

    string res;

    while(true){

        tosleep(1000);//ms

        //Sicily教你算算术！

        res = MSL.GetRes();
        if (res.size() > 0){
            SicilySend(res,5);
        }

        QClipboard *clipboard = QApplication::clipboard();
        string cstr = clipboard->text().toStdString();

        bool isScript = (cstr[0] == '#' || cstr[0] == '@');

        bool ex = true;
        static string mathSig = "+-*/() \t\r\n";
        for (size_t i = 0;i < cstr.size();++i){
            if (!((cstr[i] >= '0' && cstr[i] <= '9') || mathSig.find(cstr[i])!=string::npos)){
                ex = false;
                break;
            }
        }

        if (cstr.size() > 0 && (isScript || ex)){
            static string oldstr;
            if (oldstr.size() == cstr.size()){
                size_t len = min(64,int(cstr.size()));
                bool can = true;
                for(size_t i = 0;i < len;++i){
                    if (oldstr[i] != cstr[i]){
                        can = false;
                        break;
                    }
                }
                if(can)continue;
            }

            oldstr = cstr;

            string script;

            if (cstr[0] == '@')script = cstr.substr(1);
            else if(cstr[1] == '#')script = cstr;
            else if (ex){
                script = '#';
                for(size_t i = 0;i<cstr.size();++i){
                    char &c = cstr[i];
                    if (c == ' '||c == '\t'||c=='\r'||c=='\n')continue;
                    script += c;
                }
            }
            MSL.Eval(script);

        }

    }
    return a.exec();
}
