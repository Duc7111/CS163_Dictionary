#include "LL.h"

#include "AVL.h"

bNode::bNode(string k) : key(k), left(nullptr), right(nullptr){}


void bNode::clear()
{
    if(left) left->clear();
    if(right) right->clear();
    delete this;
}

AVL::AVL() : root(nullptr){}
AVL::~AVL()
{
    root->clear();
}

bNode* AVL::insert(string k)
{
    //insert phase
    stack<bNode*> s;
    bNode* temp = root;
    while(temp)
    {
        if(temp->key == k) return temp;
        if(temp->key > k)
            if(temp->left)
            {
                s.push(temp);
                temp = temp->left;
            }
            else
            {
                temp->left = new bNode(k);
                break;
            }
        else
            if(temp->right)
            {
                s.push(temp);
                temp = temp->right;
            }
            else
            {
                temp->right = new bNode(k);
                break;
            }
    }
    //balancing phase   
}