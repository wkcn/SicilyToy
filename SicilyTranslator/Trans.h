#ifndef TRANS_H
#define TRANS_H
#define _CRT_SECURE_NO_WARNINGS
//使用Python
#define _USING_PYTHON 0

#include "../ToyDef.h"

#if _USING_PYTHON
#include <Python.h>
#endif

#include <QString>
#include <QThread>

#include <fstream>
#include <string>
#include <cstring>
using namespace std;

struct TrieNode{
    //TrieNode *children[26];
    TrieNode **children;
    char size;
    char *value;
    TrieNode();
    ~TrieNode();
    void Set(const string &name);
};

class TrieTree{
private:
    TrieNode *root;
    static char ids[26];
public:
    TrieTree();
    ~TrieTree();
    void insert(string word,string content);
    string find(string word);
};

class Trans : public QThread
{
    Q_OBJECT

public:
    Trans();
    ~Trans();
private:
    string res;
    string ori;
    string cstr;
    TrieTree trieTree;
#if _USING_PYTHON
private:
    PyObject *pTransModule;
    PyObject *searchDict;
    PyObject *translate;
#endif
protected:
    void run();

public:
    void ReadFile(const  char *filename);
    void Set(const string &text);
    string Get();
    string GerOrigin();
    //ing代表正在翻译
    //finished代表翻译完成
    volatile bool ing;
    volatile bool finished;
};
#endif // TRANS_H
