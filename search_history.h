#pragma once

#include "Main.h"

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

