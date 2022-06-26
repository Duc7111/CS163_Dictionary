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


