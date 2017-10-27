//
//  PlacesCollection.hpp
//  LoneliestPlace
//
//  Created by David Crooks on 27/10/2017.
//  Copyright © 2017 David Crooks. All rights reserved.
//

#ifndef PlacesCollection_hpp
#define PlacesCollection_hpp

#include <stdio.h>

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
public:

    PlaceCollection(istream &inputStream);
    PlaceCollection(int n);
    
    Place mostIsolated();
    
    /* Adaptor interface for nanaoflann k-d tree  */
    
    inline size_t kdtree_get_point_count() const { return places.size(); }
    
    inline double kdtree_get_pt(const size_t idx, int dim) const
    {
        if (dim == 0) return double(places[idx].x);
        else return double(places[idx].y);
    }
    
    template <class BBOX>
    bool kdtree_get_bbox(BBOX& /*bb*/) const { return false; }
    
private:
    vector<Place> places;
};



#endif /* PlacesCollection_hpp */
