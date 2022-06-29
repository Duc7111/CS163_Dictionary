#include "search.h"


vector<string> search_for_def (bNode* root,string dir)
{
    vector<string> str;
    int num = 0, size_def = 0;
    char *tmp;
    string tmps;
    ifstream fin (dir,ios::binary);
    fin.seekg(root->d);
    fin.read ((char*) &num,sizeof(int));
    num += 1;
    for (int i = 0 ; i < num ; i++)
    {
        fin.read((char*) &size_def,sizeof(int));
        tmp = new char [size_def + 1];
        fin.read(tmp, size_def);
        tmps = tmp;
        str.push_back(tmps);
        delete [] tmp;
    }
    return str;
}

vector<vector<string>> random_word (AVL tree, string dir, int n)
{
    /*
    vector<vector<string>> strs;
    vector<string> tmp, def;
    bNode* p;
    int pos, opt, j, randef, h = tree.height(tree.get_root());
    vector<bool> dup;
    dup.resize(h + 1);
    fill(dup.begin(), dup.end(), false);
    srand(time(NULL));
    for (int i = 0 ; i<4 ; i++)
    {
        p = tree.get_root();
        tmp.clear();
        j = 0;
        do
        {
            pos = rand() % (h + 1);
        }while (dup[pos] == true);
        dup[pos] = true;
        while (j != pos)
        {
            opt = rand() % 3;
            if (p->left == nullptr && p->right == nullptr)
            {
                break;
            }
            if (p->left != nullptr)
            {
                if (opt == 1 || (opt == 2 && p->right == nullptr))
                {
                    p = p->left;
                }
            }
            if (p->right != nullptr)
            {
                if (opt == 2|| (opt == 1 && p->left == nullptr))
                {
                    p = p->right;
                }
            }
            j++;
        }
        tmp.push_back(p->key);
        def = search_for_def(p, dir);
        randef = rand() % def.size();
        tmp.push_back(def[randef]);
        strs.push_back(tmp);
    }
     */
    vector<bNode*> arr;
    vector <vector<string>> strs;
    vector <int> lists;
    bNode* root = tree.get_root();
    srand(time(NULL));
    for (int i = 0 ; i<4 ; i++)
    {
        int tmp = rand() % (n + 1);
        lists.push_back(tmp);
    }
    sort (lists.begin(),lists.end());
    vector<bNode*> nodes = random_take(root, lists);
    for (int j = 0 ; j<4 ; j++)
    {
        vector <string> stmps;
        stmps.push_back(nodes[j]->key);
        vector<string> def_str  = search_for_def(tree.search(nodes[j]->key), dir);
        stmps.push_back(def_str[rand()%(def_str.size())]);
        strs.push_back(stmps);
    }
    return strs;
}

vector<bNode*> random_take (bNode* root , vector<int> lists) //sorted list
{
    int num = 0;
    vector<bNode*> nodes;
    queue<bNode*> qu;
    qu.push(root);
    for (int i = 0; i < 4 ; i++)
    {
        while (num != lists[i])
        {
            num += 1;
            bNode* tmp = (qu.dequeue())->data;
            if (tmp->left != nullptr)
                qu.push(tmp->left);
            if (tmp->right != nullptr)
                qu.push(tmp->right);
        }
        nodes.push_back(qu.rear());
    }
    return nodes;
}
