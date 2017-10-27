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

struct PlaceCollection
{
    vector<Place> places;
    
    PlaceCollection(ifstream &inputFile){
        Place p;
        
        while (inputFile >> p.name) {
            
            inputFile >> p.x;
            inputFile >> p.y;
            
            places.push_back(p);
        }
    }
    
    /* Adaptor interface for nanaoflann k-d tree  */
    
    inline size_t kdtree_get_point_count() const { return places.size(); }
    
    inline double kdtree_get_pt(const size_t idx, int dim) const
    {
        if (dim == 0) return double(places[idx].x);
        else return double(places[idx].y);
    }
    
    template <class BBOX>
    bool kdtree_get_bbox(BBOX& /*bb*/) const { return false; }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    ifstream inputFile;
    
    inputFile.open("/Users/decrooks/Developer/WRLD/cpp/LoneliestPlace/LoneliestPlace/problem_small.txt");
    
    if (!inputFile) {
        cerr << "Unable to open file";
        exit(1);   // call system to stop
    }
    
    auto placeCollection = PlaceCollection(inputFile);
    
    for(auto p:placeCollection.places){
        cout << p.name << endl;
    }
    
    cout << "done" << endl;
    
    return 0;
}
