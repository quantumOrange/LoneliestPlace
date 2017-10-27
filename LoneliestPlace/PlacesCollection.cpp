//
//  PlacesCollection.cpp
//  LoneliestPlace
//
//  Created by David Crooks on 27/10/2017.
//  Copyright © 2017 David Crooks. All rights reserved.
//
#include <stdlib.h>
#include "PlacesCollection.hpp"
#include "nanoflann.hpp"


using namespace nanoflann;


/*
     init with stream of place data.
*/
PlaceCollection::PlaceCollection(std::istream &inputStream){
    Place p;
    
    while (inputStream >> p.name) {
        
        inputStream >> p.x;
        inputStream >> p.y;
        
        places.push_back(p);
    }
}

/*
     init with n random places.
*/
PlaceCollection::PlaceCollection(int n){
    
    Place p;
    
    for(int i=0; i< n; i++){
        
        p.name = "place" + std::to_string(i);
        p.x = rand()%10000;
        p.y = rand()%10000;

        places.push_back(p);
        
    }
}

/*
     Finds the most isolated place in the collection.
     performance: O(n log n).
*/
Place PlaceCollection::mostIsolated(){
    
    //Create a k-d tree.
    //A k-d tree is data structure for spacial data that supports fast (O(log n)) look up of nearest neighbours.
    //https://en.wikipedia.org/wiki/K-d_tree
    //I'm using the nanoflann implementaion of the k-d tree data structure.
    //https://github.com/jlblancoc/nanoflann
    
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
   
    double maxDistanceSq = 0;
    
    Place  mostIsolatedPlace;
    
    //find nearest neighbour for each place, saving that place if it is the most isolated so far.
    for(auto place: places){
        
        //clear the result set
        resultSet.init(ret_index, out_dist_sqr );
        
        //create a test point from the current place
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
