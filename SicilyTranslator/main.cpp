#include <QApplication>
#include <QtNetwork>
#include <QClipboard>

#include "Trans.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);//使用这个才能使用剪贴板！

    Trans trans;
    /* sleep直接调用内核的指令,所在线程挂起,CPU搜索执行队列的重排序Timer每次会在线程池中取新的线程来执行,存在多次访问线程池的损耗 */

    while(true){

        tosleep(1000);//ms

        //Sicily教你翻译！

        QClipboard *clipboard = QApplication::clipboard();
        string cstr = clipboard->text().toStdString();

        if (cstr.size() > 0){
            trans.Set(cstr);
        }

        if(trans.finished){
            string mes;
            string res = trans.Get();
            string transStr = trans.GerOrigin();
            if(res != transStr){
                if(res.size()>0){
                    mes = transStr;
                    mes += "\n   意思是： ≥▽≤\n";
                    mes += res;
                    SicilySend(mes,5);
                }else{
                    mes = "不知道啊 (。_。)";
                    SicilySend(mes);
                }
            }else{
                mes = "不知道 ≥﹏≤";
                SicilySend(mes);
            }

        }
    }

    return a.exec();
}
