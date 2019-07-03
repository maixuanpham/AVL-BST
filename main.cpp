//
//  main.cpp
//  Project 4
//
//  Created by Mai Pham on 11/22/17.
//  Copyright © 2017 Mai Pham. All rights reserved.
//

#include "AVLTree.h"
#include "bst.h"
#include "PopulationRecord.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
    string code;                            // county/state code
    string population;                      // population
    string name;                            // county/state name
    
    string input;                           // input file data
    string separated;                       // separated file data
    int menu;                               // menu selection
    AVLTree avlt;                           // AVL search tree
    SearchTree bst;                         // BST tree
    
    cout << "Project 4 for DATA STRUCTURE 1 (PROF. T.VO)\n";
    cout << "Author: Mai Pham\n\n";
    
    ifstream inputFile;
    inputFile.open("p4large.txt");
    if (!inputFile)
    {
        cout << "Error opening file. \n";
        cout << "The file was not found\n\n";
        return 1;
    }
    
    while (!inputFile.eof())
    {
        getline(inputFile,input);
        stringstream ss(input);
        
        getline(ss, separated, ',');
        code = separated;
        getline(ss, separated, ',');
        population = separated;
        getline(ss, separated, '\n');
        name = separated;
        
        PopulationRecord rec (code, population, name);
        avlt.insert(code, rec);
        bst.insert(code, rec);
    }
    
    cout << "Menu: \n";
    cout << "1. Search for a record\n";
    cout << "2. Insert a record\n";
    cout << "3. Delete a record\n";
    cout << "4. List all record\n";
    cout << "5. Exit\n\n";
    cout << "Select an option: ";
    cin >> menu;
    cout << endl;
    while (menu != 5)
    {
        switch (menu)
        {
            case 1:
            {
                cout << "Searching for a record...\n";
                cout << "Please enter the county/state code: ";
                cin >> code;
                bst.find(code);                                 // for bst time purpose
                AVLTree::Iterator iterator = avlt.find(code);
                PopulationRecord temp = (*iterator).value();
                cout << "ID: " << temp.getCode()<< "\tPopulation: " << temp.getPopulation() << "  \tCounty/State: " << temp.getName()<< endl;
                cout << "AVL Time: " << avlt.getCount() << " milliseconds." << endl;
                cout << "BST Time: " << bst.getCount() << " milliseconds." << endl;
                break;
            }
            case 2:
            {
                cout << "Inserting a record...\n";
                cout << "Please enter the county/state code, population, & name: ";
                cin >> code >> population;
                cin.ignore();
                getline(cin, name);
                cout << "Inputting...\n";
                cout << "ID: " << code<< "\tPopulation: " << population << "   \tCounty/State: " << name << endl;
                PopulationRecord rec (code, population, name);
                avlt.insert(code, rec);
                bst.insert(code, rec);
                cout << "AVL Time: " << avlt.getCount() << " milliseconds." << endl;
                cout << "BST Time: " << bst.getCount() << " milliseconds." << endl;
                cout << "Completed!" << endl;
                break;
            }
            case 3:
            {
                cout << "Deleting a record...\n";
                cout << "Please enter the county/state code to delete: ";
                cin >> code;
                avlt.erase(code);
                bst.erase(code);
                cout << "AVL Time: " << avlt.getCount() << " milliseconds." << endl;
                cout << "BST Time: " << bst.getCount() << " milliseconds." << endl;
                cout << "Completed!" << endl;
                break;
            }
            case 4:
            {
                cout << "Displaying the record.\n";
                AVLTree::Iterator iterator = avlt.begin();
                ++iterator;
                while(!(iterator == avlt.end()))
                {
                    PopulationRecord temp = (*iterator).value();
                    cout << "ID: " << temp.getCode()<< "\tPopulation: " << temp.getPopulation() << "   \tCounty/State: " << temp.getName()<< endl;
                    ++iterator;
                }
                break;
            }
        }
        cout << "\nMenu: \n";
        cout << "1. Search for a record\n";
        cout << "2. Insert a record\n";
        cout << "3. Delete a record\n";
        cout << "4. List all record\n";
        cout << "5. Exit\n\n";
        cout << "Select an option: ";
        cin >> menu;
    }
    return 0;
}


