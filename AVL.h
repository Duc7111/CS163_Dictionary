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

    bNode();
    bNode(string, int);

    bool add(bNode*&);

    void clear();

    int height();
    void updateH();
    
    void Add(string word, string dir);
    void save(ofstream&);
    void load(ifstream&);
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

    bool maketree(string, string);
    bool insert(string, int);
    bool remove(string);//unnessessary

    bNode* search(string);

    bool load(ifstream&);
    bool save(ofstream&);
    int Add(AVL& ,string ,string ,string);
    bNode* get_root ()
    {
        return root;
    }
    int height (bNode* tree);
};
