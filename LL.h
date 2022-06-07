#pragma once

template<class T>
struct Node
{
    T data;
    Node* next;

    Node() : next(nullptr){}
    Node(T, Node* n) : data(T), next(n);
};

template<class T>
struct stack
{
    private:
        Node<T>* head;
    public:
        stack() : head(nullptr){}

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

        void clear()
        {
            while(head)
            {
                Node<T>* temp = head;
                head = head->next;
                delete temp;
            }
        }
};