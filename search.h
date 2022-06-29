#ifndef search_h
#define search_h


#endif /* search_h */
#include "AVL.h"
#include "LL.h"
#include <cstring>
#include <vector>
#include <iostream>
#include <ctime>
using namespace std;

vector<string> search_for_def (bNode* root,string dir);
vector<bNode*> random_take (bNode* root, vector<int> lists);
vector<vector<string>> random_word (AVL tree, string dir, int n);
