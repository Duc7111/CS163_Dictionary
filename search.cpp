#include "search.h"


string search_for_def (AVL tree,string word,string dir)
{
    string str;
    bNode* node;
    node = tree.search(word);
    ifstream fin (dir, ios::binary);
    fin.seekg(node -> d,ios::cur);
    fin.read((char*) &str, 500);
    return str;
}


