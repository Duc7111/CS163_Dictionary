#pragma once

#include "AVL.h"
#include "LL.h"

class FL
{
    private:
        bNode** arr;
        int m_size, c_size;
        Node<bNode*>* t_arr;
    public:
        FL(int);
        ~FL();

        bNode*& operator[](int);
        
        void AoR(bNode*);
        bool remove(int);

        bool save(string);
};