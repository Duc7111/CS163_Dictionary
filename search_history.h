#pragma once

#include "Main.h"

class search_history {
private:
	Node<wstring>*& hist_head;
public:
	Node<wstring>* Load(string hist_dir);
	Node<wstring>* Add(wstring word, string hist_dir);
	Node<wstring>* Delete();
	void View();
};

