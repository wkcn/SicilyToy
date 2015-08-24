#include "Trans.h"

TrieNode::TrieNode(){
    value = 0;
    size = 0;
    //for(auto &c:children) c = 0;
}

TrieNode::~TrieNode(){
    if(!value)delete value;
    for (int i = 0; i < size;++i){
        if (children[i])delete children[i];
    }
    //for(auto &c:children) if(c)delete c;
}

void TrieNode::Set(const string &name){
    size_t len = name.length();
    //value = new char[len + 1];
    //strcpy(value,name.c_str());
    value = new char[len + 1];
    for (size_t i = 0;i < len;++i)
        value[i] = name[i];
    value[len] = '\0';
}

char TrieTree::ids[26];

TrieTree::TrieTree(){
    root = new TrieNode;
    const char freq[26] = {'e','a','i','t','o','r','n','s','l','c','u','d','p','h','m','g','f','b','y','w','v','k','x','z','j','q'};//字母出现频率
    char id = 0;
    for (char c : freq){
        ids[c - 'a'] = id++;
    }
}

TrieTree::~TrieTree(){
    delete root;
}

void TrieTree::insert(string word, string content){
    TrieNode *node = root;
    int id;
    for(auto c:word){
        if(c >= 'a' && c <= 'z')id = c - 'a';
        else if(c >= 'A' && c <= 'Z')id = c - 'A';
        else continue;

        //一般字典树 -> 无频率统计的放缩字典树 -> 带频率统计的放缩字典树
        //105M -> 63M -> 52M

        id = ids[id];

        if (id >= node->size){
            TrieNode **nn = new TrieNode*[id + 1];
            for (int i = 0;i < node->size;++i)nn[i] = node->children[i];//拷贝指针
            for (int i = node->size;i <= id;++i)nn[i] = 0;
            if(node->size > 0)delete [] node->children;
            node->children = nn;
            node->size = id + 1;
        }

        if(!node -> children[id])node -> children[id] = new TrieNode;
        node = node -> children[id];

    }
    node->Set(content);
}

string TrieTree::find(string word){
    TrieNode *node = root;
    int id;
    bool ok = false;
    for(auto c:word){
        if(c >= 'a' && c <= 'z')id = c - 'a';
        else if(c >= 'A' && c <= 'Z')id = c - 'A';
        else continue;

        id = ids[id];

        if(id >= node->size || node->children[id] == 0)return "";

        node = node -> children[id];
        ok = true;
    }

    if (!ok || node->value == 0)return "";
    return node -> value;
}

Trans::Trans(){

    //Trie Tree

    for(int i=0;i<26;i++){
        string name = "Dict\\";
        name += char(i+'a');
        name += ".txt";
        ReadFile(GetStdFileDir(name).c_str());
    }

    for(int i=0;i<26;i++){
        string name = "Dict\\Plus\\";
        name += char(i+'a');
        name += ".txt";
        ReadFile(GetStdFileDir(name).c_str());
    }

#if _USING_PYTHON
    //Python
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("reload(sys)");

    //添加路径
    PyRun_SimpleString("sys.path.append('./')");
    string path = "sys.path.append(\'" + GetStdFileDir("Python//") + "\')";
    qDebug("%s",path.c_str());
    PyRun_SimpleString(path.c_str());

    PyRun_SimpleString("sys.setdefaultencoding('utf-8')");

    pTransModule = PyImport_ImportModule("Trans");

    searchDict = PyObject_GetAttrString(pTransModule,"Dict");
    translate = PyObject_GetAttrString(pTransModule,"Translate");
#endif

    finished = false;
    ing = false;
}

Trans::~Trans(){

}

void Trans::ReadFile(const char *filename){
    string buf;
    ifstream fin(filename);
    if(fin.fail())return;
    getline(fin,buf);
    while(!fin.eof()){
        size_t q;
        string word;
        for(q=0;q<buf.size();q++){
            if(buf[q]=='~')break;
            word += buf[q];
        }
        string content;
        for(size_t u=q+1;u<buf.size();u++){
            if(buf[u]=='|')content += '\n';
            else content += buf[u];
        }
        trieTree.insert(word,content);
        getline(fin,buf);
    }
    fin.close();
}

void Trans::Set(const string& text){
    if (!ing){
        finished = false;
        cstr = text;
        start();
    }
}
string Trans::Get(){
    finished = false;
    ing = false;
    return res;
}
string Trans::GerOrigin(){
    return ori;
}
void Trans::run(){
    const int maxLen = 128;
    bool first = true;
    string temp;
    int count = 0;
    for(auto c:cstr){
        if(first && (c == ' ' || c == '\n' || c == '\r' || c == '\t'))continue;
        temp += c;
        count ++;
        if(count > maxLen)break;
        first = false;
    }

    if(temp != ori){
        ing = true;
        ori = temp;

        res = trieTree.find(temp);
#if _USING_PYTHON
        if (res.empty()){
            //use network
            static char s[] = "s";
            PyObject *re = PyObject_CallFunction(searchDict,s,temp.c_str());
            res = PyString_AsString(re);
            if (!res.empty()){
                //add to addition dictionary
                string smallword;
                string means;
                bool isword = true;
                for (auto &c:temp){
                    if (c >= 'A' && c <='Z')smallword += c - 'A' + 'a';
                    else {
                        smallword += c;
                        if (!((c >= 'a' && c <= 'z') || c == ' ')){
                            isword = false;
                            break;
                        }
                    }
                }
                if (isword){
                    for (auto &c:res){
                        if (c == '\n')means += '|';
                        else means += c;
                    }
                    if (means.back() == '|')means.pop_back();

                    string name = "Dict\\Plus\\";
                    name += char(smallword[0]);
                    name += ".txt";
                    ofstream fout(GetStdFileDir(name).c_str(),ios::app);
                    fout << smallword << '~' << means << endl;
                    trieTree.insert(smallword,res);
                }
            }else{
                bool ex = true;
                static string mathSig = "+-*/() \t\r\n";
                for (size_t i = 0;i < cstr.size();++i){
                    if (!((cstr[i] >= '0' && cstr[i] <= '9') || mathSig.find(cstr[i])!=string::npos)){
                        ex = false;
                        break;
                    }
                }
                if (!ex){
                    PyObject *re = PyObject_CallFunction(translate,s,temp.c_str());
                    res = PyString_AsString(re);
                }
            }
        }
#endif

        finished = true;
    }
}
