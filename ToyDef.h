#ifndef SICILY_TOY_DEFINE
#define SICILY_TOY_DEFINE

#include <QApplication>
#include <QtNetwork>
#include <QClipboard>
#include <QFileDialog>
#include <QString>
#include <QTimer>
#include <string>
#include <map>

//windows 的编码问题
#if defined(WIN32)
#pragma execution_character_set("utf-8")
#endif

using namespace std;

const QHostAddress UDPaddr = QHostAddress("127.0.0.1");
const int UDPport = 3939;

QDir DirectoryOf(const QString &subdir);
QString GetFileDir(QString file);
string GetStdFileDir(string file);


class SicilyToy : public QObject{
    Q_OBJECT
public:
    SicilyToy();
    void Send(const string &mes,int life = 0);
private slots:
    void Play();
private:
    QTimer *timer;
};

#endif
