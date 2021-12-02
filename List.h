#pragma once
#include <vector>
#include <stdio.h>



using namespace std;



template<typename T>
class List
{
public:
    
    List();
    ~List();
    void push_back(T Data);
    int size();
    void pop_front();
    void del_el(int index);
    void push_front(T Data);
    void add_el(T Data, int index);
    void pop_back();
    T& operator[](int index);



    
private:
    template<typename T>
    class Node
    {
    public:
        Node* Next;
        T Data;
        Node(T Data = T(), Node* Next = nullptr) {
            this->Data = Data;
            this->Next = Next;
        }
    };
    int Size;
    Node<T>* Head;
    
};

template<typename T>
List<T>::List()
{
    Size = 0;
    Head = nullptr;
}
template<typename T>
List<T>::~List()
{

}

template<typename T>
void List<T>::push_back(T Data)
{
    if (size() == 0) {
        Head = new Node<T>(Data);
    }
    else {
        Node<T>* Cur = Head;
        while (Cur->Next != nullptr) {
            Cur = Cur->Next;
        }
        Cur->Next = new Node<T>(Data);
    }
    Size++;
}

template<typename T>
int List<T>::size()
{
    return Size;
}

template<typename T>
void List<T>::pop_front()
{
    Node<T>* Next_Node = Head->Next;
    delete Head;
    Head = Next_Node;
    Size--;
}

template<typename T>
void List<T>::del_el(int index)
{
    {
        Node<T>* prev = this->Head;
        if (index == 0) {
            pop_front();
        }
        else {
            for (int i = 0; i + 1 < index; i++) {
                prev = prev->Next;
            }
            Node<T>* cur = prev->Next;
            prev->Next = cur->Next;
            Size--;
        }
    }
}

template<typename T>
void List<T>::push_front(T Data)
{
    {

        if (Size == 0) {
            Head = new Node<T>(Data);
        }
        else {
            Node<T>* PreviousHead = Head;
            Head = new Node<T>(Data);
            Head->Next = PreviousHead;
        }

        Size++;
    }

}

template<typename T>
void List<T>::add_el(T Data, int index)
{
    if (index == 0) {
        push_front();
    }
    else {
        Node<T>* Cur = Head;
        for (int i = 0; i < index; i++) {
            Cur = Cur->Next;
        }
        Node<T>* Cur_Next = Cur->Next;
        Cur->Next = new Node<T>(Data);
        Cur->Next = Cur_Next;
        Size++;
    }
}

template<typename T>
void List<T>::pop_back()
{
    del_el(size() - 1);
}

template<typename T>
T& List<T>::operator[](int index)
{
    Node<T>* Cur = Head;
    for (int i = 0; i < index; i++) {
        Cur = Cur->Next;
    }
    return Cur->Data;
}








 