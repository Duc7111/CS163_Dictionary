#include "AVL.h"
#include "Const.h"

bNode::bNode(string k, int D) : key(k), d(D), f(false), left(nullptr), right(nullptr){}

bool bNode::add(string k, int D)
{
    if(key == k) return false;
    if(key > k)
        if(left) return left->add(k, D);
        else left = new bNode(k, D);
    else
        if(right) return right->add(k, D);
        else right = new bNode(k, D);
    return true;
}

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

void bNode::save(ofstream& fout)
{
    int s = key.length();
    fout.write((char*)&s, sizeof(int));
    fout.write(&key[0], s);
    fout.write((char*)&d, sizeof(int));
}

AVL::AVL() : root(nullptr){}
AVL::~AVL()
{
    root->clear();
}

bNode* AVL::insert(string k, int d)
{
    //insert phase
    stacks<bNode*> s;
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
                temp->left = new bNode(k, d);
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
                temp->right = new bNode(k, d);
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
    return root;
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

bool AVL::load(string dir)
{
    ifstream fin(dir, ios_base::binary);
    if(!fin.is_open()) return false;
    int k;
    fin.read((char*)&k, sizeof(int));
    string s;
    fin.read(&s[0], k);
    fin.read((char*)&k, sizeof(int));
    root = new bNode(s, k);
    while(!fin.eof())
    {
        fin.read((char*)&k, sizeof(int));
        fin.read(&s[0], k);
        fin.read((char*)&k, sizeof(int));
        if(!root->add(s, k)) return false;
    }
    return true;
}

bool AVL::save(string dir)
{
    if(root == nullptr) return true;
    ofstream fout(dir, ios_base::binary);
    if(!fout.is_open()) return false;
    queue<bNode*> q; q.push(root);
    while(!q.empty())
    {
        bNode* temp = q.front();
        if(temp->left) q.push(temp->left);
        if(temp->right) q.push(temp->right);
        temp->save(fout);
        q.pop();
    }
    return true;
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
