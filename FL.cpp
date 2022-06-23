#include "FL.h"

FL::FL(int size) : arr(new bNode*[size]), m_size(size), c_size(size)
{
    t_arr = new Node<bNode*>(new bNode("errMSG", -1), nullptr);
}

FL::~FL()
{
    delete[] arr;
    t_arr->clear();
}

bNode*& FL::operator[](int i)
{
    if(i < m_size) return arr[i];
    i -= m_size;
    Node<bNode*>* temp = t_arr;
    while(i--)
    {
        if(temp->data->d != -1) temp = temp->next;
        else return temp->data;
    }
    return temp->data;
}

bool FL::add(bNode* b)
{
    if(b->f) return false;
    if(m_size > c_size) arr[c_size] = b;
    else t_arr = new Node<bNode*>(b, t_arr);
    ++c_size;
    return true;
}

bool FL::remove(int i)
{
    if(i < c_size)
    {
        while(i < c_size)
        {
            arr[i] = arr[i + 1];
            ++i;
        }
        return true;
    }
    else
    {
        i -= c_size;
        if(t_arr->data->d == -1) return false;
        Node<bNode*>* temp = t_arr;
        if(i == 0)
        {
            t_arr = t_arr->next;
            delete temp;
            --c_size;
            return true;
        }
        while(--i)
        {
            temp = temp->next;
            if(temp->data->d == -1) return false;
        }
        Node<bNode*>* t = temp->next;
        temp->next = t->next;
        delete t;
        --c_size;
        return true;
    }
}

bool FL::save(string dir)
{
    ofstream fout(dir, ios_base::binary);
    if(!fout.is_open()) return false;
    int s = c_size;
    Node<bNode*>* temp = t_arr;
    while(temp->data->d != -1)
    {
        ++s;
        temp = temp->next;
    }
    fout.write((char*)&s, sizeof(int));
    return true;
}