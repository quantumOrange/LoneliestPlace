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
//#include <string>
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
    
    Place mostIsolated(){
        //Create a k-d tree
        const int dim = 2;
        
        typedef KDTreeSingleIndexAdaptor<
        L2_Simple_Adaptor<double, PlaceCollection> ,
        PlaceCollection,
        dim
        > KD_tree_t;
        
        KD_tree_t   tree(dim, *this, KDTreeSingleIndexAdaptorParams(10 /* max leaf */) );
        tree.buildIndex();
        
        const size_t num_results = 2;
        size_t ret_index[2];
        double out_dist_sqr[2];
        nanoflann::KNNResultSet<double> resultSet(num_results);
        resultSet.init(ret_index, out_dist_sqr );
        
        double maxDistanceSq = 0;

        Place  mostIsolatedPlace;
        
        //find nearest neighbour for each place, saving that place if it is the most isolated so far.
        for(auto place: places){
            
            resultSet.init(ret_index, out_dist_sqr );
            ///create a test point from the current place
            double query_pt[dim] = {double(place.x) , double(place.y)};
            //find the two nearest neighbours for the test point. The first should be the current place itself, the second will be its nearest neighbour.
            tree.findNeighbors(resultSet, &query_pt[0], nanoflann::SearchParams(10));
            
            if (out_dist_sqr[1] > maxDistanceSq ) {
                //The current place is the most isolated so far.
                maxDistanceSq = out_dist_sqr[1];
                mostIsolatedPlace = place;
            }
        }
        
        return mostIsolatedPlace;
    };
    
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
    
    cout << "Please input the path to a file containing a list of places:" << endl;
    
    string filePath;
    
    cin >> filePath;
    
    inputFile.open(filePath);
    
    if (!inputFile) {
        cerr << "Unable to open file";
        exit(1);   // call system to stop
    }
    
    auto placeCollection = PlaceCollection(inputFile);
    clock_t begin = clock();
    Place mostIsolatedPlace = placeCollection.mostIsolated();
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    std::cout << "Most Isolated Place is: " << mostIsolatedPlace.name << endl;
     std::cout << "Found in: " << elapsed_secs << " seconds" << endl;
    cout << "done" << endl;
    
    return 0;
}
