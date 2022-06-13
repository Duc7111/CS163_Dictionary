#pragma once

#include<string>
#include<fstream>
#include "LL.h"

using namespace std;

struct bNode
{
    string key;
    int d;
    bool f;
    bNode *left, *right;

    bNode(string, int);

    bool add(string, int);

    void clear();

    int height();
    void Add(string word, string dir);
    void save(ofstream&);
};

class AVL
{
private:
    bNode* root;
public:
    AVL();
    ~AVL();

    bool maketree(string);
    bNode* insert(string, int);
    bool remove(string k);//unnessessary

    bNode* search(string);

    bool load(string);
    bool save(string);
    bNode* Add(AVL,string, int,string,string);
};

bNode* lrotate(bNode*);
bNode* rrotate(bNode*);
