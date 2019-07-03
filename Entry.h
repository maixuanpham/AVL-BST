#ifndef ENTRY_H
#define ENTRY_H
// Modified for CSCI 220 Fall 15

#include "PopulationRecord.h"
#include <string>
#include <iostream>
using namespace std;

class Entry
{					                                            // a (key, value) pair
public:						                                    // public functions
    string Key;				                                    // key type
    PopulationRecord Value;			                                // value type
	Entry(const string& k = "", const PopulationRecord& v = PopulationRecord())	// constructor
      : _key(k), _value(v) { }	
    const string& key() const { return _key; }		            // get key
    const PopulationRecord& value() const { return _value; }	    // get value
    void setKey(const string& k) { _key = k; }		            // set key
    void setValue(const PopulationRecord& v) { _value = v; }	    // set value
private:						                                // private data
    string _key;						                        // key
    PopulationRecord _value;					                    // value
};
#endif
