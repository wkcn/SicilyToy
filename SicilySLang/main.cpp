#include <QApplication>
#include <QtNetwork>
#include <QClipboard>
#include <QFileDialog>
#include <QString>

#include <algorithm>
using namespace std;

#include "MultiSLang.h"

QDir directoryOf(const QString &subdir)
{
    QDir dir(QApplication::applicationDirPath());

#if defined(Q_OS_WIN)
    if (dir.dirName().toLower() == "debug"
            || dir.dirName().toLower() == "release"
            || dir.dirName().toLower() == "bin")
        dir.cdUp();
#elif defined(Q_OS_MAC)
    if (dir.dirName() == "MacOS"){
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
    }
#endif
    dir.cd(subdir);
    return dir;
}


QString GetFileDir(QString file){
#if !defined(WIN32)
    file = file.replace("\\","//");
#endif
    return directoryOf("").absoluteFilePath(file);
}

QString GetQDir(QString file){
    return GetFileDir(file);
}

string GetDataDir(string file){
    return GetFileDir(QString::fromStdString(file)).toStdString();
}

const QHostAddress addr = QHostAddress("127.0.0.1");
const int port = 3939;

inline void Send(string &mes,QUdpSocket *sender,int life = 0){
    mes += char(life);
    sender->writeDatagram(mes.c_str(),mes.size(),addr,port);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);//使用这个才能使用剪贴板！

    //那个TCP有缓存= =
    QUdpSocket *sender;
    sender = new QUdpSocket();

    srand(unsigned int(time(0)));
    SVM::AddPath(GetDataDir("Data\\SLang\\"));

    MultiSLang MSL;

    //cout.rdbuf(mes.rdbuf());//重定向有乱码

    string res;

    while(true){

        Sleep(1000);//ms

        //Sicily教你算算术！

        res = MSL.GetRes();
        if (res.size() > 0){
            Send(res,sender,5);
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
                size_t len = min(64,cstr.size());
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
            if (ex){
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
