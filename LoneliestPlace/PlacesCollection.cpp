//
//  PlacesCollection.cpp
//  LoneliestPlace
//
//  Created by David Crooks on 27/10/2017.
//  Copyright © 2017 David Crooks. All rights reserved.
//

#include "PlacesCollection.hpp"


/*
template<typename S>
PlaceCollection::PlaceCollection(S &inputStream){
    Place p;
    
    while (inputStream >> p.name) {
        
        inputStream >> p.x;
        inputStream >> p.y;
        
        places.push_back(p);
    }
}
*/
PlaceCollection::PlaceCollection(fstream &inputStream){
    Place p;
    
    while (inputStream >> p.name) {
        
        inputStream >> p.x;
        inputStream >> p.y;
        
        places.push_back(p);
    }
}

PlaceCollection::PlaceCollection(istream &inputStream){
    Place p;
    
    while (inputStream >> p.name) {
        
        inputStream >> p.x;
        inputStream >> p.y;
        
        places.push_back(p);
    }
}


/*
     Find the most isolated place in the collection.
     O(n log n), I think.
*/
Place PlaceCollection::mostIsolated(){
    //Create a k-d tree
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
