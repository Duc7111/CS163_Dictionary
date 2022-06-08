#pragma once

#include<string>
#include<fstream>

using namespace std;

struct bNode
{
    string key;
    int d;
    bNode *left, *right;

    bNode(string k);

    void clear();

    int height();
};

class AVL
{
private:
    bNode* root;
public:
    AVL();
    ~AVL();

    bool maketree(string dir);
    bNode* insert(string k);
    bool remove(string k);

    bNode* search(string x);

    bool read(string dir);
    bool save(string dir);
};

bNode* lrotate(bNode* root);
bNode* rrotate(bNode* root);