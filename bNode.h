#pragma once

#include<fstream>
#include<string>

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

    int height();
    void updateH();
    
    void Add(string word, string dir);
    void save(ofstream&);
    void load(ifstream&);
};

void clear(bNode*&);