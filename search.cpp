#include "search.h"
#include <iomanip>
#include <algorithm>

using namespace std;


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

vector<vector<string>> random_word (AVL& tree, string dir, int n)
{
    vector <vector<string>> strs;
    vector<bNode*> arr;
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
        stmps.push_back(def_str[rand()%(def_str.size() - 1)]);
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
            Node<bNode*>* tmp1 = qu.dequeue();
            bNode* tmp = tmp1 -> data;
            if (tmp->left != nullptr)
                qu.push(tmp->left);
            if (tmp->right != nullptr)
                qu.push(tmp->right);
            //delete tmp1;
        }
        nodes.push_back(qu.rear());
    }
    return nodes;
}

bool random_game (vector<vector<string>> lists)
{
    if (lists.empty())
        return false;
    int random,t = 0,tmp, choice, cmp;
    srand(time(NULL));
    vector <bool> is_take;
    is_take.resize(4);
    fill(is_take.begin(),is_take.end(),false);
    random = rand()%4;
    cout << "Can you guess the meaning of "<< char(34)  << lists[random][0] << char(34) << " ?" << endl;
    while (t < 4)
    {
        do
        {
            tmp = rand() % 4;
        }while (is_take[tmp] == true);
        is_take[tmp] = true;
        if (tmp == random)
            cmp = t;
        cout << setw(10) << t + 1 << ". " << lists[tmp][1] << endl;
        t += 1;
    }
    do
    {
        cout << "your choice: ";
        cin >> choice;
    }while (choice <= 0 || choice > 4);
    if (choice == cmp + 1)
    {
        cout << "you win" << endl;
        return true;
    }
    else
    {
        cout << "you've lost" << endl;
        return false;
    }
}

void random_keywords (vector<vector<string>> lists)
{
    for (int i = 0 ; i<4 ; i++)
    {
        cout << lists[i][0] << ". " << lists[i][1] << endl;
    }
}

bool random_def_game (vector<vector<string>> lists)
{
    srand(time(NULL));
    vector<bool> is_visited;
    is_visited.resize(4);
    fill (is_visited.begin(),is_visited.end(),false);
    int random = rand() % 4 , tmp , ctmp, choice;
    cout << "Can you guess the meaning of "<< char(34) << lists[random][1] << char (34) << " ?" << endl;
    for (int i = 0 ; i<4 ; i++)
    {
        do
        {
            ctmp = rand()%4;
        }while (is_visited[ctmp] == true);
        is_visited[ctmp] = true;
        if (ctmp == random)
        {
            tmp = i+1;
        }
        cout << setw(10) << i+1 << ". " << lists[i][0] << endl;
    }
    do
    {
        cout << "your choice: ";
        cin >> choice;
    }while (choice <= 0 || choice > 4);
    if (choice == random + 1)
    {
        cout <<"you win" << endl;
        return true;
    }
    else
    {
        cout << "you've lost" << endl;
        return false;
    }
}
