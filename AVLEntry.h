//
//  AVLEntry.h
//  Project
//
//  Created by Mai Pham on 11/28/17.
//  Copyright © 2017 Mai Pham. All rights reserved.
//

#ifndef AVLEntry_h
#define AVLEntry_h

#include "PopulationRecord.h"
#include "Entry.h"
#include <string>
#include <iostream>
using namespace std;

class AVLEntry : public Entry {                // an AVL entry
private:
    int ht;                                 // node height
protected:                                  // local types
    int height() const { return ht; }            // get height
    void setHeight(int h) { ht = h; }            // set height
public:                        // public functions
    AVLEntry(const string& k = "", const PopulationRecord& v = PopulationRecord())    // constructor
    : Entry(k,v), ht(0) { }
    friend class AVLTree;                // allow AVLTree access
};

#endif /* AVLEntry_h */
