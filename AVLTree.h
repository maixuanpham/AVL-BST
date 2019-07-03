//
//  AVLTree.h
//  Project
//
//  Created by Mai Pham on 11/28/17.
//  Copyright © 2017 Mai Pham. All rights reserved.
//

#ifndef AVLTree_h
#define AVLTree_h
#include "bst.h"

// an AVL tree
class AVLTree : public SearchTree
{
public:                                                 // public types
    typedef SearchTree::Iterator Iterator;                      // an iterator
protected:                                              // local types
    typedef SearchTree ST;                                      // a search tree

// public functions
public:
    AVLTree(): ST() { }                                 // constructor
    Iterator insert(const string& k, const PopulationRecord& x)            // insert (k,x)
    {
        count = 0;
        TPos v = inserter(k, x);                        // insert in base tree
        setHeight(v);                                   // compute its height
        rebalance(v);                                   // rebalance if needed
        return Iterator(v);
    }
    void erase(const string& k) throw(NonexistentElement)    // remove key k entry
    {
        count = 0;
        TPos v = finder(k, ST::root());                 // find in base tree
        if (Iterator(v) == ST::end())                   // not found?
            throw NonexistentElement("Erase of nonexistent");
        TPos w = eraser(v);                             // remove it
        rebalance(w);                                   // rebalance if needed
    }
    void erase(const Iterator& p);                      // remove entry at p

// utility functions
protected:
    int height(const TPos& v) const                    // node height utility
        { return (v.isExternal() ? 0 : v.v->elt.height()); }
    void setHeight(TPos v)                             // set height utility
    {
        int hl = height(v.left());
        int hr = height(v.right());
        v.v->elt.setHeight(1 + std::max(hl, hr));            // max of left & right
    }
    bool isBalanced(const TPos& v) const               // is v balanced?
    {
        int bal = height(v.left()) - height(v.right());
        return ((-1 <= bal) && (bal <= 1));
    }
    TPos tallGrandchild(const TPos& v) const           // get tallest grandchild
    {
        TPos zl = v.left();
        TPos zr = v.right();
        if (height(zl) >= height(zr))                   // left child taller
            if (height(zl.left()) >= height(zl.right()))
                return zl.left();
            else
                return zl.right();
        else                                            // right child taller
            if (height(zr.right()) >= height(zr.left()))
                return zr.right();
            else
                return zr.left();
    }
    void rebalance(const TPos& v)                      // rebalance utility
    {
        TPos z = v;
        while (!(z.v == ST::root().v)) {                    // rebalance up to root
            z = z.parent();
            setHeight(z);                               // compute new height
            if (!isBalanced(z)) {                       // restructuring needed
                TPos x = tallGrandchild(z);
                z = restructure(x);                     // trinode restructure
                setHeight(z.left());                    // update heights
                setHeight(z.right());
                setHeight(z);
            }
        }
    }
};

#endif /* AVLTree_h */
