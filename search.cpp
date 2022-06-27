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

vector<vector<string>> random_word (AVL tree,string dir)
{
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
    return strs;
}

