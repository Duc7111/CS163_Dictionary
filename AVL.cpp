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
    return h;
}

void bNode::updateH()
{
    h = left->height();
    if(right->height() > h) h = right->h;
    ++h;
}

void bNode::save(ofstream& fout)
{
    int s = key.length();
    fout.write((char*)&s, sizeof(int));
    fout.write(&key[0], s);
    fout.write((char*)&d, sizeof(int));
}

bool AVL::subadd(bNode*& root, string k, int x)
{
    if(!root) root = new bNode(k, x);
    if(root->key == k) return false;
    bool b;
    if(root->key > k) b = subadd(root->left, k, x);
    else b = subadd(root->right, k, x);
    if(!b) return false;
    int l = root->left->height(), r = root->right->height();
    if(l - r == 2) rrotate(root);
    else if(r - l == 2) lrotate(root);
    else root->updateH();
    return true;
}

AVL::AVL() : root(nullptr){}
AVL::~AVL()
{
    root->clear();
}

bool AVL::insert(string k, int d)
{
    return subadd(root, k, d);
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

void AVL::lrotate(bNode*& root)
{
    if(!root->right) return;
    bNode* temp = root->right;
    if(root->right->left && root->right->left->height() > root->right->right->height())
    {
        root ->right = temp->left;
        temp->left = temp->left->right;
        root->right->right = temp;
        temp = root->right;
        temp->right->updateH();
    }
    root->right = temp->left;
    root->updateH();
    temp->left = root;
    root = temp;
    root->updateH();
}

void AVL::rrotate(bNode*& root)
{
    if(!root->left) return;
    bNode* temp = root->left;
    if(root->left->right && root->left->right->height() > root->left->left->height())
    {
        root ->left = temp->right;
        temp->right = temp->right->left;
        root->left->left = temp;
        temp = root->left;
        temp->left->updateH();
    }
    root->left = temp->right;
    root->updateH();
    temp->right = root;
    root = temp;
    root->updateH();
}
