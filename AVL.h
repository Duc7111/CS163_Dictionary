#pragma once

#include<string>
#include<fstream>

using namespace std;

struct bNode
{
    string key;
    int d;
    bNode *left, *right;

    bNode();

    void clear();

    bNode* insert(string k, int& MSG);
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
    int height();

    bool read(string dir);
    bool save(string dir);
};