//
//  PopulationRecord.h
//  Project
//
//  Created by Mai Pham on 11/29/17.
//  Copyright © 2017 Mai Pham. All rights reserved.
//

#ifndef PopulationRecord_h
#define PopulationRecord_h

#include <string>
#include <iostream>
using namespace std;

class PopulationRecord
{
private:
    string code;                            // county/state code
    string population;                      // population
    string name;                            // county/state name
public:
    PopulationRecord()
    {
        code = "";
        population = "";
        name = "";
    }
    PopulationRecord(string c, string p, string n)
    {
        code = c;
        population = p;
        name = n;
    }
    string getCode()
        {   return code; }
    string getPopulation()
    {   return population; }
    string getName()
    {   return name; }
};

#endif /* PopulationRecord_h */
