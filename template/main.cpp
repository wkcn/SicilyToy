#include "../ToyDef.h"

void SicilyToy::Play(){
    Send("哈哈",5);
}

int main(int argc,char *argv[]){
    QCoreApplication a(argc, argv);
    SicilyToy toy;
    return a.exec();
}
