#include "ToyDef.h"

QDir DirectoryOf(const QString &subdir) {
    static map<QString,QDir> ma;
    static QDir dir(QApplication::applicationDirPath());
    if (ma.count(subdir)){
        return ma[subdir];
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

    ma[subdir] = dir;
    return dir;
}


QString GetFileDir(QString file){ 
    #if !defined(WIN32)
        file = file.replace("\\","//");
    #endif
    return DirectoryOf("").absoluteFilePath(file);
}
string GetFileDir(string file){
    return GetFileDir(QString::fromStdString(file)).toStdString();
}

SicilyToy::SicilyToy(){
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(Play()));
    timer -> start(1000);
}

void SicilyToy::Send(const string &mes,int life){
    static QUdpSocket *sender = new QUdpSocket();
    int len = mes.length();
    char *cstr = new char[len + 1];
    strncpy(cstr,mes.c_str(),len);
    cstr[len] = char(life);

    sender->writeDatagram(cstr,len + 1,UDPaddr,UDPport);
}
