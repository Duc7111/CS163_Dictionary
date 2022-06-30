#pragma once

#include <iostream>
#include "AVL.h"
#include "LL.h"
#include <vector>
#include <fstream>

void load_search_history(Node<string>*& search_history, string dir);
Node<string>* add_search_history(Node<string>*& search_history, string word, string dir);
void view_search_history(Node<string>* search_history);
Node<string>* delete_search_history(Node<string>* search_history);