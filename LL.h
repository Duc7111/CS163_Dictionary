#pragma once

template<class T>
struct Node
{
    T data;
    Node* next;

    Node() : next(nullptr){}
    Node(T a, Node* n) : data(a), next(n){}
    void clear()
    {
        if(this == nullptr) return;
        next->clear();
        next->clear();
        delete this;
    }
};

template<class T>
struct stacks
{
    private:
        Node<T>* head;
    public:
        stacks() : head(nullptr){}
        ~stacks()
        {
            head->clear();
        }

        void push(T a)
        {
            head = new Node(a, head);
        }

        bool pop()
        {
            if(!head) return false;
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            return true;
        }

        T top()
        {
            return head->data;
        }

        bool empty()
        {
            if(head) return false;
            return true;
        }

        void clear()
        {
            head->clear;
            head = nullptr;
        }
};

template<class T>
struct queue
{
    private:
        Node<T> *head, *tail;
    public:
        queue()
        {
            head = new Node<T>;
            tail = head;
        }
        ~queue()
        {
            head->clear();
        }
        
        void push(T a)
        {
            tail -> next = new Node<T> (a, nullptr);
            tail = tail->next;
        }

        void pop()
        {
            Node<T>* temp = head->next;
            head->next = temp->next;
            delete temp;
        }

        T front()
        {
            return head->next->data;
        }

        bool empty()
        {
            if(head->next == nullptr) return true;
            return false;
        }

        void clear()
        {
            head->next->clear();
            tail = head;
        }
};
