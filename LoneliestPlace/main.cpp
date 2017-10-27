//
//  main.cpp
//  LoneliestPlace
//
//  Created by David Crooks on 27/10/2017.
//  Copyright © 2017 David Crooks. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

#include "nanoflann.hpp"
using namespace std;
using namespace nanoflann;

struct Place {
    int x,y;
    string name;
};

vector<Place> places;
int main(int argc, const char * argv[]) {
    // insert code here...
    ifstream inputFile;
    

    inputFile.open("/Users/decrooks/Developer/WRLD/cpp/LoneliestPlace/LoneliestPlace/problem_small.txt");
    
    if (!inputFile) {
        cerr << "Unable to open file";
        exit(1);   // call system to stop
    }
    
    Place p;
    
    cout << "Reading data...";
    
    while (inputFile >> p.name) {
        
        inputFile >> p.x;
        inputFile >> p.y;
        
        
        places.push_back(p);
    }
    
    cout << "done" << endl;
    
    return 0;
}
