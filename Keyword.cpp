#include<algorithm>

#include"Keyword.h"
#include"Const.h"

keyword::keyword() : key(), link(nullptr){}

keyword::keyword(const wstring& k, bNode* l) : key(key)
{
    link = new Node<bNode*>(l, nullptr);
}

keyword::~keyword()
{
    if(link) link->clear();
}

int c_hash::hf(const wstring& key)
{
    int val = 0;
    for(wchar_t c : key) val = (val*7 + c)%hash_len;
    return val;
}

c_hash::c_hash() : arr{}{}

Node<keyword>*& c_hash::get(const wstring& key)
{
    Node<keyword>*& temp = arr[hf(key)];
    while(temp && temp->data.key < key) temp = temp->next;
    return temp; 
}

void c_hash::add(const wstring& key, bNode* link)
{
    Node<keyword>*& temp = get(key);
    if(!temp || temp->data.key != key) temp = new Node(keyword(key, link), temp);
    else
    {
        Node<bNode*>*& t = temp->data.link;
        while(t->data->key < link->key) t = t->next;
        if(t->data->key != link->key) t = new Node(link, t);
    }
}

wstring getWord(const wstring &def, int &i, const int &n)
{
    wstring temp;
    while(i < n && def[i] != L' ') temp += def[i++];
    ++i;
    return temp;
}

vector<wstring> getKeyWord(const wstring &def)
{
    int l = def.length(), i = 0;
    vector<wstring> sol;
    while(i < l)
    {
        wstring temp = getWord(def, i, l);
        int len = temp.length();
        while(len > 2 && temp[len - 1] < 48 || (temp[len - 1] > 57 && temp[len - 1] < 65) || (temp[len - 1] > 122 && temp[len - 1] < 192))
        {
            len--;
            temp.pop_back();
        }
        while(len > 2 &&temp[0] < 48 || (temp[0] > 57 && temp[0] < 65) || (temp[0] > 122 && temp[0] < 192))
        {
            len--;
            temp.erase(temp.begin());
        }
        if(len > 2) 
        {
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            if(temp != L"the" && temp != L"and") sol.push_back(temp);
        }
    }
    return sol;
}