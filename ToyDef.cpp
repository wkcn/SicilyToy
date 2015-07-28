#include "ToyDef.h"

#if defined(WIN32)
void tosleep(int s){Sleep(s);}
#else
void tosleep(int s){usleep(s*1000);}
#endif

QDir directoryOf(const QString &subdir) { 
    static bool firstdir = true;
    static QDir dir(QApplication::applicationDirPath());
    if (!firstdir){
        return dir;
    }

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

    firstdir = false;
    return dir;
}


QString GetFileDir(QString file){ 
#if !defined(WIN32)
    file = file.replace("\\","//");
#endif
    return directoryOf("").absoluteFilePath(file);
}

string GetStdFileDir(string file){ 
    return GetFileDir(QString::fromStdString(file)).toStdString();
}


void SicilySend(string &mes,int life){
	static QUdpSocket *sender = new QUdpSocket();
    mes += char(life);
    sender->writeDatagram(mes.c_str(),mes.size(),addr,port);
}
