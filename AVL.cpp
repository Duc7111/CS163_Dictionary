#include "LL.h"

#include "AVL.h"

bNode::bNode(string k) : key(k), left(nullptr), right(nullptr){}


void bNode::clear()
{
    if(left) left->clear();
    if(right) right->clear();
    delete this;
}

int bNode::height()
{
    if(this == nullptr) return 0;
    int l = left->height(), r = right->height();
    if(l > r) return l;
    return r;
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
    while(!s.empty())
    {
        if(s.top()->left->height() - s.top()->right->height() == 2)
        {
            if(s.top() != root)
            {
                temp = s.top(); s.pop();
                if(s.top()->left == temp) s.top()->left = rrotate(temp);
                else s.top()->left = rrotate(temp);
            }
            else root = rrotate(root);
            return nullptr;
        }
        if(s.top()->right->height() - s.top()->left->height() == 2)
        {
            if(s.top() != root)
            {
                temp = s.top(); s.pop();
                if(s.top()->left == temp) s.top()->left = lrotate(temp);
                else s.top()->left = lrotate(temp);
            }
            else root = lrotate(root);
            return nullptr;
        }
    }
}

bNode* AVL::search(string x)
{
    bNode* temp = root;
    while(temp)
    {
        if(temp->key > x) temp = temp->left;
        else if(temp->key < x) temp = temp->right;
        else break;
    }
    return temp;
}

bNode* lrotate(bNode* root)
{
    bNode* temp;
    if(root->right->left->height() > root->right->right->height())
    {
        temp = root->right;
        root->right = temp->left;
        temp->left = temp->left->right;
        root->right->right = temp;
    }
    temp = root;
    root = root->right;
    temp->right = root->left;
    root->left = temp;
    return root;
}

bNode* rrotate(bNode* root)
{
    bNode* temp;
    if(root->left->right->height() > root->left->left->height())
    {
        temp = root->left;
        root->left = temp->right;
        temp->right = temp->right->left;
        root->left->left = temp;
    }
    temp = root;
    root = root->left;
    temp->left = root->right;
    root->right = temp;
    return root;
}