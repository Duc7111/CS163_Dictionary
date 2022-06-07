#include "AVL.h"

bNode::bNode() : left(nullptr), right(nullptr){}


void bNode::clear()
{
    if(left) left->clear();
    if(right) right->clear();
    delete this;
}

bNode* insert(string k, int& MSG)
{
    
}

AVL::AVL() : root(nullptr){}
AVL::~AVL()
{
    root->clear();
}

bNode* insert(string k)
{
    
}