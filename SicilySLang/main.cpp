#include "../ToyDef.h"
#include "MultiSLang.h"
MultiSLang MSL;

void SicilyToy::Play(){

    //Sicily教你算算术！
    string res = MSL.GetRes();
    if (res.size() > 0){
        qDebug("res:%s",res.c_str());
        Send(res,3);
    }

    QClipboard *clipboard = QApplication::clipboard();
    string cstr = clipboard->text().toStdString();

    bool isScript = (cstr[0] == '#' || cstr[0] == '@');

    bool ex = true;
    static string mathSig = "+-*/^\'() \t\r\n";
    for (size_t i = 0;i < cstr.size();++i){
        if (!(((cstr[i] >= '0' && cstr[i] <= '9') || cstr[i] == 'x') || mathSig.find(cstr[i])!=string::npos)){
            ex = false;
            return;
        }
    }

    if (cstr.size() > 0 && (isScript || ex)){
        static string oldstr;
        if (oldstr.size() == cstr.size()){
            size_t len = min(64,int(cstr.size()));
            bool same = true;
            for(size_t i = 0;i < len;++i){
                if (oldstr[i] != cstr[i]){
                    same = false;
                    break;
                }
            }
            if(same)return;
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
        //qDebug("%s",script.c_str());
        MSL.Eval(script);

    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);//使用这个才能使用剪贴板！
    srand(size_t(time(0)));
    SicilyToy toy;
    return a.exec();
}
