#include<iostream>
#include<codecvt>
#include<io.h>
#include<fcntl.h> 

#include "AVL.h"
#include "Const.h"

bNode::bNode() : left(nullptr), right(nullptr) {}
bNode::bNode(wstring s, int D) : key(s), h(1), d(D), f(false), left(nullptr), right(nullptr) {}

bool bNode::add(bNode*& root)
{
    if (key == root->key) return false;
    if (key > root->key)
        if (left) return left->add(root);
        else left = root;
    else
        if (right) return right->add(root);
        else right = root;
    return true;
}

void clear(bNode*& root)
{
    if(root->left) clear(root->left);
    if(root->right) clear(root->right);
    delete root;
    root = nullptr;
}

int bNode::height()
{
    if(this) return h;
    return 0;
}

void bNode::updateH()
{
    h = left->height() + 1;
    if (right->height() >= h) h = right->h + 1;
}

void bNode::save(ofstream& fout)
{
    int s = key.length() + 1;
    fout.write((char*)&s, sizeof(int));
    fout.write((char*)(key.c_str() + 1), s*sizeof(wchar_t));
    fout.write((char*)&h, sizeof(int));
    fout.write((char*)&d, sizeof(int));
    fout.write((char*)&f, sizeof(bool));
}

void bNode::load(ifstream& fin)
{
    int t;
    fin.read((char*)&t, sizeof(int));
    wchar_t* temp = new wchar_t[t];
    fin.read((char*)&temp, t*sizeof(wchar_t));
    key = temp;
    fin.read((char*)&h, sizeof(int));
    fin.read((char*)&d, sizeof(int));
    fin.read((char*)&f, sizeof(bool));
    delete[] temp;
}

bool AVL::subadd(bNode*& root, wstring k, int x)
{
    if (!root) 
    {
        root = new bNode(k, x);
        return true;
    }
    if (root->key == k) return false;
    bool b;
    if (root->key > k) b = subadd(root->left, k, x);
    else b = subadd(root->right, k, x);
    if (!b) return false;
    int d = root->left->height() - root->right->height();
    if (d == 2) rrotate(root);
    else if (d == -2) lrotate(root);
    else root->updateH();
    return true;
}

AVL::AVL() : root(nullptr) {}
AVL::~AVL()
{
    if(root) clear(root);
}

int AVL::maketree(string dir, string def_dir, string struct_dir)
{
    wifstream wfin(dir);
    wfin.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
    ofstream fout(def_dir, ios_base::binary | ios_base::trunc);
    if (!wfin.is_open()) return 0;
    wstring temp, cur = L"";
    int i = 0, d = 0, c = 0;
    while (!wfin.eof())
    {
        getline(wfin, temp, L'\t');
        if (temp != cur)//new node
        {
            ++c;
            if(c != 1)
            {
                fout.seekp(d);
                fout.write((char*)&i, sizeof(int));
            }
            fout.seekp(0, ios_base::end);
            cur = temp;
            d = fout.tellp();
            insert(cur, d);
            fout.write((char*)&i, sizeof(int));//just make a spot for later writing
            i = 0;
        }
        getline(wfin, temp);
        int l = temp.length() + 1;
        fout.write((char*)&l, sizeof(int));
        fout.write((char*)(temp.c_str() + 1), l*sizeof(wchar_t));
        ++i;
    }
    fout.close();
    fout.open(struct_dir, ios_base::binary | ios_base::trunc);
    int t = 0;
    fout.write((char*)&t, sizeof(int));
    save(fout);
    fout.close();
    return c;
}

bool AVL::insert(wstring k, int d)
{
    return subadd(root, k, d);
}

bool AVL::remove(wstring k)
{
    return true;
}

bNode* AVL::search(wstring x)
{
    bNode* temp = root;
    while (temp)
    {
        if (temp->key > x) temp = temp->left;
        else if (temp->key < x) temp = temp->right;
        else break;
    }
    return temp;
}

int AVL::load(ifstream& fin, FL& fl)
{
    int fl_size; fin.read((char*)&fl_size, sizeof(int));
    fl = FL(fl_size);
    root = new bNode;
    root->load(fin);
    int c = 1;
    while (!fin.eof())
    {
        bNode* temp = new bNode; temp->load(fin);
        root->add(temp);
        if(temp->f) fl.AoR(temp);
        ++c;
    }
    return c;
}

bool AVL::save(ofstream& fout)
{
    if (root == nullptr) return true;
    if (!fout.is_open()) return false;
    queue<bNode*> q; q.push(root);
    while (!q.empty())
    {
        bNode* temp = q.front();
        if (temp->left) q.push(temp->left);
        if (temp->right) q.push(temp->right);
        temp->save(fout);
        q.pop();
    }
    return true;
}

void AVL::lrotate(bNode*& root)
{
    if (!root->right) return;
    bNode* temp = root->right;
    if (root->right->left && root->right->left->height() > root->right->right->height())
    {
        root->right = temp->left;
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
    if (!root->left) return;
    bNode* temp = root->left;
    if (root->left->right && root->left->right->height() > root->left->left->height())
    {
        root->left = temp->right;
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

int AVL::height(bNode* tree)
{
    if (tree == nullptr)
        return 0;
    int sleft, sright;
    sleft = height(tree->left);
    sright = height(tree->right);
    if (sleft > sright)
        return sleft + 1;
    else
        return sright + 1;
}

void AVL::num_of_words(bNode* root, int& a)
{
    if (root == nullptr)
        return;
    num_of_words(root->left, a);
    num_of_words(root->right, a);
    a += 1;
}