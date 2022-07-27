#pragma once

#include<iostream>
#include<fstream>
#include<iomanip>
#include<io.h>
#include<fcntl.h>
#include<string>
#include<codecvt>

#include "LL.h"
using namespace std;

class search_history {
private:
	Node<wstring>* hist_head;
public:
	search_history();
	Node<wstring>* Load();
	Node<wstring>* Add(wstring word);
	Node<wstring>* Delete();
	void View();
};

bool check_empty_file(wifstream& fin);