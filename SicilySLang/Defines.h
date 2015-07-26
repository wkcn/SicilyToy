﻿#ifndef SLANG_DEFINES_H
#define SLANG_DEFINES_H
#define _CRT_SECURE_NO_WARNINGS
#include "BigInt.h"
#include "../ToyDef.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <stack>
#include <map>
#include <cstdlib>
#include <ctime>
#include <cstdio>
using namespace std;

//windows 的编码问题
#if defined(WIN32)
#pragma execution_character_set("utf-8")
#include <windows.h>
#else
#include <unistd.h>
#endif

struct SExp{
	enum SEXP_TYPE{
		VAR, FUNC, COMMAND, IF, WHILE,STR
	};
	SEXP_TYPE type;
	string name;
	SExp *parent;
	int id;
	Vector<SExp*> elems;	//不知道为什么，自己写的Vector不能查看详细元素赋值
	SExp();
	void Copy(SExp *);
};

void DelSExp(SExp *);

#endif
