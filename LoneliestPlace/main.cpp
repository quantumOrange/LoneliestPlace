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
    
    //Create a k-d tree
    const int dim = 2;
    
    typedef KDTreeSingleIndexAdaptor<
    L2_Simple_Adaptor<double, PlaceCollection> ,
    PlaceCollection,
    dim
    > KD_tree_t;
    
    
    KD_tree_t   tree(dim, placeCollection, KDTreeSingleIndexAdaptorParams(10 /* max leaf */) );
    tree.buildIndex();
    
    const size_t num_results = 2;
    size_t ret_index[2];
    double out_dist_sqr[2];
    nanoflann::KNNResultSet<double> resultSet(num_results);
    resultSet.init(ret_index, out_dist_sqr );
    
    
    double maxDistanceSq = 0;
    //int mostIsolatedIndex = side;
    Place  mostIsolatedPlace;
    
    for(auto place: placeCollection.places){
        
        resultSet.init(ret_index, out_dist_sqr );
        double query_pt[dim] = {double(place.x) , double(place.y)};
        tree.findNeighbors(resultSet, &query_pt[0], nanoflann::SearchParams(10));
        
        // cout << place.name << " -> " << "place" <<ret_index[1] << "  d = " << out_dist_sqr[1] <<endl;
        
        if (out_dist_sqr[1] > maxDistanceSq ) {
            
            //std::cout << " !!!!!!!!" << out_dist_sqr[1] << endl;
            maxDistanceSq = out_dist_sqr[1];
            mostIsolatedPlace = place;
            
        }
    }
    
    std::cout << "Most Isolated Place is: " << mostIsolatedPlace.name << endl;
    
    cout << "done" << endl;
    
    return 0;
}
