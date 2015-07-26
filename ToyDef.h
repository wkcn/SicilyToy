#ifndef SICILY_TOY_DEFINE
#define SICILY_TOY_DEFINE

#include <QApplication>
#include <QtNetwork>
#include <QClipboard>
#include <QFileDialog>
#include <QString>

#include <string>
using namespace std;

const QHostAddress addr = QHostAddress("127.0.0.1");
const int port = 3939;

//windows 的编码问题
#if defined(WIN32)
#pragma execution_character_set("utf-8")
#include <windows.h>
#else
#include <unistd.h>
#endif

QDir directoryOf(const QString &subdir);

QString GetFileDir(QString file);

string GetStdFileDir(string file);

void SicilySend(string &mes,int life = 0);

void tosleep(int s);

#endif
