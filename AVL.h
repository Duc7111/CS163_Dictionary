#pragma once

#include<string>
#include<fstream>
#include<vector>

#include "LL.h"
#include "FL.h"
#include "bNode.h"

using namespace std;

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

    int maketree(string, string);
    bool insert(string, int);
    bool remove(string);//unnessessary

    bNode* search(string);

    int load(ifstream&, FL&);
    bool save(ofstream&);
    int Add(AVL& ,string ,string ,string);
    bNode* get_root ()
    {
        return root;
    }
    int height (bNode*);
    void num_of_words (bNode*, int&);
};
