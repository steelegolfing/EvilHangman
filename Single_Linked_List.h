//
//  AVL_Tree.h
//  Project 3 - AVL Tree
//
//  Created by Travis Cox on 2/11/17.
//  Copyright © 2017 Travis Cox. All rights reserved.
//

#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

#include <algorithm>
#include <ostream>
#include <queue>
using namespace std;


class UnderflowException{ };

template <typename T>
class singleLinkedList
{
public:
    singleLinkedList()
    {
        head = NULL;
        tail = NULL;
        size = 0;
    }
    singleLinkedList(const singleLinkedList & right)
    {
        size = 0;
        head = NULL;
        tail = NULL;
        clone(right);
        
    }
    singleLinkedList(singleLinkedList && right)
    {
        head = right.head;
        tail = right.tail;
        size = right.size;
        
        right.head = NULL;
        right.tail = NULL;
        size = 0;
    }
    ~singleLinkedList()
    {
        makeEmpty();
    }
    singleLinkedList& operator=(const singleLinkedList & right)
    {
        if (this != &right)
        {
            makeEmpty();
            clone(right);
        }
        
        return *this;
    }
    singleLinkedList& operator=(singleLinkedList && right)
    {
        std::swap(head, right.head);
        std::swap(tail, right.tail);
        size = right.size;
        
        return *this;
    }
    void makeEmpty()
    {
        if (size > 0)
        {
            Node *temp;
            while(head != tail)
            {
                temp = head;
                head = head->next;
                delete temp;
                size--;
            }
            temp = head;
            head = NULL;
            tail = NULL;
            delete temp;
            size--;
        }
    }
    bool isEmpty()
    {
        return (size == 0);
    }
    void insert(T &temp)
    {
        Node *tempNode = new Node(temp, NULL);
        if(size == 0)
        {
            head = tempNode;
            tail = tempNode;
        }
        else
        {
            tail->next = tempNode;
            tail = tail->next;
        }
        size++;
    }
    int getSize()
    {
        return size;
    }
    void remove(T &temp)
    {
        if(size > 0)
        {
            Node *tempNode = head;
            temp = head->element;
            //cout << "Size: " << size << "\t";
            //cout << "Word: " << temp << endl;
            if (head == tail)
            {
                tail = tail->next;
            }
            head = head->next;
            delete tempNode;
            size--;
        }
    }
    T findHead()
    {
        if (head == NULL)
        {
            throw UnderflowException{};
        }
        
        return head->element;
    }
    void printList()
    {
        if(size == 0)
        {
            cout << "Empty list" << endl;
        }
        else
        {
            Node *tempNode = head;
            while(tempNode)
            {
                cout << tempNode->element << endl;
                tempNode = tempNode->next;
            }
        }
    }
private:
    struct Node
    {
        T element;
        Node   *next;
        
        Node( const T & ele, Node *nxt)
        {
            element = ele;
            next = nxt;
        }
        
        Node( T && ele, Node *nxt )
        {
            element = move( ele );
            next = nxt;
        }
    };
    Node *head, *tail;
    int size;
    void clone(const singleLinkedList &right)
    {
        Node *tempNode = right.head;
        while (tempNode != NULL)
        {
            insert(tempNode->element);
            tempNode = tempNode->next;
        }
    }
};

#endif /* SINGLE_LINKED_LIST_h */
