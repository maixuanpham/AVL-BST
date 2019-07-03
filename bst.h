#ifndef BST_H
#define BST_H
// Modified for CSCI 220 Fall 15

#include <string>
#include "PopulationRecord.h"
#include "BinaryTree.h"
#include "RuntimeException.h"

class SearchTree {				                        // a binary search tree
public:
    class Iterator;					                // an iterator/position
private:                                                		// member data
    BinaryTree T;                                       		// the binary tree
    int n;                                              		// number of entries
protected:
    int count;
public:
    SearchTree(): T(), n(0)
    { count = 0;T.addRoot(); T.expandExternal(T.root()); }		// create the super root
    int size() const; 					                // number of entries
    bool empty() const;					                // is the tree empty?
    int getCount()
        { return count;}
    Iterator find(const string& k)
    {
        count = 0;
		TPos v = finder(k, root());				 // search from virtual root
		if (!v.isExternal()) return Iterator(v);		 // found it
		else return end();					 // didn't find it
    }
    Iterator insert(const string& k, const PopulationRecord& x)		 // insert (k,x)
        { count = 0;TPos v = inserter(k, x); return Iterator(v); }
    void erase(const string& k)
    {
        count = 0;
		TPos v = finder(k, root());				 // search from virtual root
		if (v.isExternal())					 // not found?
		  throw NonexistentElement("Erase of nonexistent");
		eraser(v);						 // remove it
    }
    void erase( Iterator& p)			            		// remove entry at p
        { eraser(p.v); }
    Iterator begin()
    {
		TPos v = root();					// start at virtual root
		while (!v.isExternal()) v = v.left();		    	// find leftmost node
		return Iterator(v.parent());
	  }
    Iterator end()					                // iterator to end entry
        { return Iterator(T.root()); }			        	// return the super root

protected:						                // local utilities
    typedef BinaryTree::Position TPos;		    			// position in the tree
    TPos root() const    { return T.root().left(); }    		// left child of super root
    TPos finder(const string& k, const TPos& v)
    {
        count++;
		if (v.isExternal()) return v;			        // key not found
		if (k < v.v->elt.key()) return finder(k, v.left());	// search left subtree
		else if (v.v->elt.key() < k) return finder(k, v.right());	// search right subtree
		else return v;					                // found it here
    }
    TPos inserter(const string& k, const PopulationRecord& x)
    {
		TPos v = finder(k, root());				        // search from virtual root
		while (!v.isExternal())				            	// key already exists?
		  v = finder(k, v.right());				        // look further
		T.expandExternal(v);				            	// add new internal node
		(*v).setKey(k); (*v).setValue(x);			    	// set entry
		n++;						                // one more entry
		return v;						        // return insert position
    }
    TPos eraser(TPos& v) {
		TPos w;
		if (v.left().isExternal()) w = v.left();			// remove from left
		else if (v.right().isExternal()) w = v.right();			// remove from right
		else {								// both internal?
		  w = v.right();						// go to right subtree
		  do { w = w.left(); } while (!w.isExternal());			// get leftmost node
		  TPos u = w.parent();
		  (*v).setKey((*u).key()); (*v).setValue((*u).value());		// copy w's parent to v
		}
		n--;								// one less entry
		return T.removeAboveExternal(w);				// remove w and parent
    }

    TPos restructure(const TPos& v) 			    			// restructure
    {
        TPos x, y, z, a, b, c, t0, t1, t2, t3;
        
        // node x with parent y and grandparent z
        x = v;
        y = x.v->par;
        z = y.v->par;

        if (z.left().v == y.v)
        {
            if (y.left().v == x.v)
            {
                a = x;
                b = y;
                c = z;
                t0 = x.left();
                t1 = x.right();
                t2 = y.right();
                t3 = z.right();
            }
            else
            {
                a = y;
                b = x;
                c = z;
                t0 = y.left();
                t1 = x.left();
                t2 = x.right();
                t3 = z.right();
            }
        }
        else
        {
            if (y.left().v == x.v)
            {
                a = z;
                b = x;
                c = y;
                t0 = z.left();
                t1 = x.left();
                t2 = x.right();
                t3 = y.right();
            }
            else
            {
                a = z;
                b = y;
                c = x;
                t0 = z.left();
                t1 = y.left();
                t2 = x.left();
                t3 = x.right();
            }
        }
        
        TPos w = z.v->par;
        if (z.v == w.v->right)
            w.v->right = b.v;
        else
            w.v->left = b.v;
        
        b.v->par = w.v;
        
        // Let a be the left child of b and let T0 and T1 be the left and right subtrees of a, respectively.
        b.v->left = a.v;
        a.v->par = b.v;
        t0.v->par = a.v;
        a.v->left = t0.v;
        t1.v->par = a.v;
        a.v->right = t1.v;
        
        // Let c be the right child of b and let T2 and T3 be the left and right subtrees of a, respectively.
        b.v->right = c.v;
        c.v->par = b.v;
        c.v->left = t2.v;
        t2.v->par = c.v;
        c.v->right = t3.v;
        t3.v->par = c.v;
        
        return b;
    }
      	// throw(BoundaryViolation);

public:
    // ...insert Iterator class declaration here
    class Iterator {	                      				// an iterator/position
    private:
      TPos v;						                // which entry
    public:
      Iterator(const TPos& vv) : v(vv) { }		    		// constructor
      //const AVLEntry& operator*() const { return *v.v; }	    	// get entry (read only)
      AVLEntry& operator*() { return *v; }			        // get entry (read/write)
      bool operator==(const Iterator& p) const				// are iterators equal?
        { return v.v == p.v.v; }
      Iterator& operator++(){
		TPos w = v.right();
		if (!w.isExternal()) {				        // have right subtree?
		  do { v = w; w = w.left(); }			    	// move down left chain
		  while (!w.isExternal());
		}
		else {
		  w = v.parent();					// get parent
		  while (v.v == w.right().v)				// move up right chain
			{ v = w; w = w.parent(); }
		  v = w;						// and first link to left
		}
		return *this;
	  }

      friend class SearchTree;				        	// give search tree access
    };
};

#endif
