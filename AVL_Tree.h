//
//  AVL_Tree.h
//  Project 3 - AVL Tree
//
//  Created by Travis Cox on 2/11/17.
//  Copyright © 2017 Travis Cox. All rights reserved.
//

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm>
#include <ostream>
#include <queue>
using namespace std;

// AVL_Tree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// void printLevelTree()  --> Print tree in Level order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

class UnderflowException{ };



template <typename Comparable>
class AVL_Tree
{
public:
    AVL_Tree( ) : root{ nullptr }
    {
        size = 0;
    }
    
    AVL_Tree( const AVL_Tree & rhs ) : root{ nullptr }
    {
        size = 0;
        root = clone( rhs.root );
    }
    
    AVL_Tree( AVL_Tree && rhs ) : root{ rhs.root }
    {
        swap(rhs.size, size);
        rhs.root = nullptr;
    }
    
    ~AVL_Tree( )
    {
        makeEmpty( );
    }
    
    /**
     * Deep copy.
     */
    AVL_Tree & operator=( const AVL_Tree & rhs )
    {
        AVL_Tree copy = rhs;
        std::swap( *this, copy );
        this->size = rhs.size;
        return *this;
    }
    
    /**
     * Move.
     */
    AVL_Tree & operator=( AVL_Tree && rhs )
    {
        std::swap( root, rhs.root );
        size = rhs.size;
        return *this;
    }
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }
    
    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }
    
    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }
    
    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }
    
    /**
     * Print the tree contents in sorted order.
     */
    void printTree(ostream& out ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
    }
    
    /**
     * Print the tree contents in Level order.
     */
    void printLevelTree(ostream& out ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printLevelTree( root, out );
    }
    
    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
        size = 0;
    }
    
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
    
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
    
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root );
    }
    
    int getSize()
    {
        return size;
    }
    
private:
    
    struct AvlNode
    {
        Comparable element;
        AvlNode   *left;
        AvlNode   *right;
        int       height;
        
        AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
        : element{ ele }, left{ lt }, right{ rt }, height{ h } { }
        
        AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
        : element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
    };
    
    int size;
    AvlNode *root;
    static const int ALLOWED_IMBALANCE = 1;
    
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, AvlNode * & t )
    {
        if (t == NULL)
        {
            t = new AvlNode(x, NULL, NULL);
            size++;
        }
        else if (t->element < x)
        {
            insert(x, t->right);
        }
        else if (t->element > x)
        {
            insert(x, t->left);
        }
        
        balance(t);
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, AvlNode * & t )
    {
        if (t == NULL)
        {
            t = new AvlNode(std::move(x), NULL, NULL);
            size++;
        }
        else if (t->element < x)
        {
            insert(x, t->right);
        }
        else if (t->element > x)
        {
            insert(x, t->left);
        }
        
        balance(t);
    }
    
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, AvlNode * & t )
    {
        if (t == NULL)
        {
            return;
        }
        
        if(t->element > x)
        {
            remove(x, t->left);
        }
        else if (t->element < x)
        {
            remove(x, t->right);
        }
        else if (t->left != NULL && t->right != NULL)
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else
        {
            AvlNode *oldNode = t;
            t = (t->left != NULL) ? t->left : t->right;
            delete oldNode;
            size--;
        }
        
        balance(t);
    }
    
    // Assume t is balanced or within one of being balanced
    void balance( AvlNode * & t )
    {
        if (t == NULL)
        {
            return;
        }
        if ((height(t->left) - height(t->right)) > ALLOWED_IMBALANCE)
        {
            if (height(t->left->left) >= height(t->left->right))
            {
                rotateWithLeftChild(t);
            }
            else
            {
                doubleWithLeftChild(t);
            }
        }
        else if ((height(t->right) - height(t->left)) > ALLOWED_IMBALANCE)
        {
            if (height(t->right->right) >= height(t->right->left))
            {
                rotateWithRightChild(t);
            }
            else
            {
                doubleWithRightChild(t);
            }
        }
        
        t->height = max(height(t->left), height(t->right)) + 1;
    }
    
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t ) const
    {
        while (t->left != NULL)
        {
            t = t->left;
        }
        return t;
    }
    
    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode * findMax( AvlNode *t ) const
    {
        while (t->right != NULL)
        {
            t = t->right;
        }
        return t;
    }
    
    
    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        if (t == NULL)
        {
            return false;
        }
        else if (t->element > x)
        {
            return contains(x, t->left);
        }
        else if (t->element < x)
        {
            return contains(x, t->right);
        }
        else
        {
            return true;
        }
    }
    
    
    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( AvlNode * & t )
    {
        if (t)
        {
            AvlNode *tempLeft = t->left;
            AvlNode *tempRight = t->right;
            
            makeEmpty(tempLeft);
            makeEmpty(tempRight);
            delete t;
            t = NULL;
        }
    }
    
    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( AvlNode *t, ostream& out ) const
    {
        if(t)
        {
            printTree(t->left, out);
            out << t->element << endl;
            printTree(t->right, out);
        }
    }
    
    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printLevelTree( AvlNode *t, ostream& out ) const
    {
        queue<AvlNode *> printQueue;
        printQueue.push(t);
        while (!printQueue.empty())
        {
            AvlNode *temp = printQueue.front();
            printQueue.pop();
            
            if (temp)
            {
                out << temp->element << endl;
                printQueue.push(temp->left);
                printQueue.push(temp->right);
            }
        }
    }
    
    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t )
    {
        if (t == NULL)
        {
            return t;
        }
        
        AvlNode *tempNode = new AvlNode(t->element, clone(t->left), clone(t->right), t->height);
        size++;
        
        return tempNode;
    }
    // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height( AvlNode *t ) const
    {
        if (t == NULL)
        {
            return -1;
        }
        return t->height;
    }
    
    int max( int lhs, int rhs ) const
    {
        if (lhs <= rhs)
        {
            return rhs;
        }
        else
        {
            return lhs;
        }
    }
    
    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        
        k2->height = (max(height(k2->left), height(k2->right)) + 1);
        k1->height = (max(height(k1->left), k2->height) + 1);
        
        k2 = k1;
    }
    
    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        
        k1->height = (max(height(k1->left), height(k1->right)) + 1);
        k2->height = (max(height(k2->left), height(k2->right)) + 1);
        
        k1 = k2;
    }
    
    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( AvlNode * & k3 )
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }
    
    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( AvlNode * & k1 )
    {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }
};

#endif /* AVL_Tree_h */
