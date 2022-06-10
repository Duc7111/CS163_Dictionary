#pragma once

template<class T>
struct Node
{
    T data;
    Node* next;

    Node() : next(nullptr){}
    Node(T, Node* n) : data(T), next(n);

    void clear()
    {
        if(this == nullptr) return;
        left->clear();
        right->clear();
        delete this;
    }
};

template<class T>
struct stack
{
    private:
        Node<T>* head;
    public:
        stack() : head(nullptr){}
        ~stack()
        {
            head->clear();
        }

        void push(T)
        {
            head = new Node(T, head);
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
        
        void push(T t)
        {
            tail->next = new Node(t, nullptr);
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