/*
*   Author: Hang-In-There
*   File Name: Single_Linked_List.h
*   File Description: Each word from the dictionary is inserted into a node.
*   This linked list is manipulated/traversed by our main algorithm for
*   determining the word for each Hangman game instance.
*   Date Created: 3/29/2017
*   Date Last Modified: 4/30/2017
*/
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
    /*
     * function: class constructor
     * description: creates a new singleLinkedList structure.
     * precondition: none
     * postcondition: head and tail pointers are to NULL, size of List is 0
     * return: none
     */
    singleLinkedList<T>()
    {
        head = NULL;
        tail = NULL;
        size = 0;
    }
    
    /*
     * function: copy constructor
     * description: creates a copy of a singleLinkedList structure by 
     * calling the Node member function clone on the structure's head
     * precondition: a singleLinkedList structure (right) exists
     * postcondition: head and tail pointers are to NULL, size of List is 0.
     * right is cloned into a new singleLinkedList structure (this).
     * return: none
     */
    singleLinkedList<T>(const singleLinkedList<T> & right)
    {
        size = 0;
        head = NULL;
        tail = NULL;
        clone(right);
        
    }
    
    /*
     * function: move constructor
     * description: moves an R value singleLinkedList structure into this.
     * precondition: singleLinedList structure (right) is an R value and exists
     * postcondition: head and tail pointers are set to right's head and tail
     * addresses, size is set to right's size. right's head and tail are set to
     * NULL; right's size is set to 0.
     * return: none
     */
    singleLinkedList<T>(singleLinkedList<T> && right)
    {
        head = right.head;
        tail = right.tail;
        size = right.size;
        
        right.head = NULL;
        right.tail = NULL;
        size = 0;
    }
    
    /*
     * function: class destructor
     * description: calls makeEmpty; empties the singleLinkedList structure
     * precondition: a singleLinkedList structure exists
     * postcondition: the singeLinkedList is emptied
     * return: none
     */
    ~singleLinkedList<T>()
    {
        makeEmpty();
    }
    
    
    /*
     * function: operator=
     * description: assigns one L-value singleLinkedList structure to another
     * L-value singleLinkedList structure
     * precondition: 2 L-value singleLinkedList structures exist
     * postcondition: the returned singleLinkedList structure equals the passed
     * singleLinkedList structure (this == right)
     * return: the equivalent singleLinkedList structure (this)
     */
    singleLinkedList<T>& operator=(const singleLinkedList<T> & right)
    {
        if (this != &right)
        {
            makeEmpty();
            clone(right);
        }
        return *this;
    }
    
    
    /*
     * function: move operator=
     * description: assigns one R-value singleLinkedList structure to another
     * L-value singleLinkedList structure
     * precondition: 1 L-value singleLinkedList structure exists, 1 R-value exists
     * postcondition: the returned L-value singleLinkedList structure equals the passed
     * R-value singleLinkedList structure (this == right)
     * return: the equivalent L-value singleLinkedList structure (this)
     */
    singleLinkedList<T>& operator=(singleLinkedList<T> && right)
    {
        std::swap(head, right.head);
        std::swap(tail, right.tail);
        size = right.size;
        
        return *this;
    }
    
    /*
     * function: makeEmpty()
     * description: This function serves as the destructor for the class. The
     * singleLinkedList is interatively traversed, and each node is emptied then
     * deleted as the iteration progresses.
     * precondition: A singleLinkedList structure exists
     * postcondition: the singleLinkedList is destructed, each node being emptied
     * then deallocated. 
     * return: void
     */
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
    
    /*
     * function: isEmpty
     * description: determines if the singleLinkedList is empty or not
     * precondition: a singleLinkedList structure exists
     * postcondition: the singleLinkedList structure is not changed
     * return: true if the singleLinkedList is empty (size == 0), false
     * otherwise.
     */
    bool isEmpty()
    {
        return (size == 0);
    }
    
    /*
     * function: insert
     * description: inserts a node into the singleLinkedList structure
     * precondition: a singleLinkedList structure exists (temp)
     * postcondition: a node is added to the structure (temp)
     * return: void
     */
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
    
    /*
     * function: getSize
     * description: reports the size of the singleLinkedList
     * precondition: a singleLinkedList structure exists
     * postcondition: the singleLinkedList structure is not changed
     * return: the size of the singleLinkedList (an integer)
     */
    int getSize()
    {
        return size;
    }
    
    /*
     * function: remove
     * description: removes a node from the front of the singleLinkedList structure
     * precondition: a singleLinkedList structure exists whose size is > 0
     * postcondition: the previous head of the singleLinkedList is removed, the head
     * is now what was the previous head's next
     * return: void
     */
    void remove(T &temp)
    {
        if(size > 0)
        {
            Node *tempNode = head;
            temp = head->element;
            if (head == tail)
            {
                tail = tail->next;
            }
            head = head->next;
            delete tempNode;
            size--;
        }
    }
    
    /*
     * function: find head
     * description: finds the head of a singleLinkedList structure
     * precondition: a singleLinkedList structure exists
     * postcondition: the singleLinkedList structure is not changed if
     * the head contains an element, UnderFlowException is thrown if
     * the head has not been initialized
     * return: T, the element in the head node of the singleLinkedList
     */
    T findHead()
    {
        if (head == NULL)
        {
            throw UnderflowException{};
        }
        
        return head->element;
    }
    
    /*
     * function: printList
     * description: prints the elements in the singleLinkedList
     * precondition: a singleLinkedList structure exists
     * postcondition: the singleLinkedList is not changed
     * return: void
     */
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
    /*
     * struct: Node
     * description: the elements of the singleLinkedList
     */
    struct Node
    {
        T element;
        Node *next;
        
        Node(const T & ele, Node *nxt)
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
    
    /*
     * function: clone
     * description: iteratively creates a copy of each Node in the singleLinkedList
     * precondition: a singleLinkedList structure exists
     * postcondition: the singleLinkedList and original Nodes are not changed, but
     * a copy of each Node is made
     * return: void
     */
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
