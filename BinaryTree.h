#ifndef BINARY_TREE_H
#define BINARY_TREE_H
// Modified for CSCI 220 Fall 13

#include "AVLEntry.h"
#include <list>
using namespace std;

class BinaryTree
{
protected:
    // insert Node declaration here...
    struct Node {					    	// a node of the tree
      AVLEntry  elt;						// element value
      Node*     par;						// parent
      Node*     left;						// left child
      Node*     right;						// right child
      Node() : elt(), par(NULL), left(NULL), right(NULL) { } 	// constructor
    };
private:
    Node* _root;                                		// pointer to the root
    int n;                                      		// number of nodes
public:
    // insert Position declaration here...
    class Position {					        // position in the tree
    public:
      Node* v;						        // pointer to the node
    public:
      Position(Node* _v = NULL) : v(_v) { }			// constructor
      AVLEntry& operator*()					// get element
        { return v->elt; }
      Position left() const				        // get left child
        { return Position(v->left); }
      Position right() const				    	// get right child
        { return Position(v->right); }
      Position parent() const				    	// get parent
        { return Position(v->par); }
      bool isRoot() const				        // root of the tree?
        { return v->par == NULL; }
      bool isExternal() const				    	// an external node?
        { return v->left == NULL && v->right == NULL; }
      friend class BinaryTree;			        	// give tree access
    };
    typedef std::list<Position> PositionList;        		// list of positions

public:
    BinaryTree() : _root(NULL), n(0) { }			// constructor
    int size() const					        // number of nodes
        { return n; }
    bool empty() const					        // is tree empty?
        { return size() == 0; }
    Position root() const				        // get the root
        { return Position(_root); }
	PositionList positions() const  			// list of nodes
	{
		PositionList pl;
		preorder(_root, pl);				// preorder traversal
		return PositionList(pl);			// return resulting list
	}
	void addRoot()					        // add root to empty tree
        { _root = new Node; n = 1; }
    void expandExternal(const Position& p)			// expand external node
    {
        Node* v = p.v;                          		// p's node
        v->left = new Node;                     		// add a new left child
        v->left->par = v;                       		// v is its parent
        v->right = new Node;                    		// and a new right child
        v->right->par = v;                      		// v is its parent
        n += 2;                                 		// two more nodes
    }
    Position removeAboveExternal(const Position& p)		// remove p and parent
	{
		Node* w = p.v;  Node* v = w->par;		// get p's node and parent
		Node* sib = (w == v->left ?  v->right : v->left);
		if (v == _root) {				// child of root?
		  _root = sib;					// ...make sibling root
		  sib->par = NULL;
		}
		else {
		  Node* gpar = v->par;				// w's grandparent
		  if (v == gpar->left) gpar->left = sib;    	// replace parent by sib
		  else gpar->right = sib;
		  sib->par = gpar;
		}
		delete w; delete v;				// delete removed nodes
		n -= 2;						// two fewer nodes
		return Position(sib);
  }

// housekeeping functions omitted...
protected: 						        // local utilities
    void preorder(Node* v, PositionList& pl) const		// preorder utility
    {
        pl.push_back(Position(v));                  		// add this node
        if (v->left != NULL)                        		// traverse left subtree
            preorder(v->left, pl);
        if (v->right != NULL)                       		// traverse right subtree
            preorder(v->right, pl);
    }
};

#endif
