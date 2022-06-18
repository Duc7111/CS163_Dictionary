#pragma once

#include<string>
#include<fstream>
#include "LL.h"

using namespace std;

struct bNode
{
    string key;
    int h, d;
    bool f;
    bNode *left, *right;

    bNode(string, int);

    bool add(string, int);

    void clear();

    int height();
    void updateH();
    
    void Add(string word, string dir);
    void save(ofstream&);
};

class AVL
{
private:
    bNode* root;

    bool subadd(bNode*&, string, int);
    void lrotate(bNode*&);
    void rrotate(bNode*&);
public:
    AVL();
    ~AVL();

    bool maketree(string);
    bool insert(string, int);
    bool remove(string k);//unnessessary

    bNode* search(string);

    bool load(string);
    bool save(string);
    int Add(AVL& ,string ,string ,string);
};
