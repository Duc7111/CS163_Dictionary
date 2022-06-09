#pragma once

#include<string>
#include<fstream>

using namespace std;

struct bNode
{
    string key;
    int d;
    bNode *left, *right;

    bNode(string k, int D);

    bool add(string k, int D);

    void clear();

    int height();

    void save(ofstream& fout);
};

class AVL
{
private:
    bNode* root;
public:
    AVL();
    ~AVL();

    bool maketree(string dir);
    bNode* insert(string k, int d);
    bool remove(string k);//unnessessary

    bNode* search(string x);

    bool load(string dir);
    bool save(string dir);
};

bNode* lrotate(bNode* root);
bNode* rrotate(bNode* root);