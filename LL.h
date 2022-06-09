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
        ~stack()
        {
            while(head)
            {
                Node<T>* temp = head;
                head = head->next;
                delete temp;
            }
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
            while(head)
            {
                Node<T>* temp = head;
                head = head->next;
                delete temp;
            }
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
            while(head)
            {
                tail = head;
                head = head->next;
                delete tail;
            }
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
};