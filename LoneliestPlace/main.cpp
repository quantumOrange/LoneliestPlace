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
#include "PlacesCollection.hpp"

using namespace std;
using namespace nanoflann;

void findMostIsolated(PlaceCollection placeCollection) {
    clock_t begin = clock();
    Place mostIsolatedPlace = placeCollection.mostIsolated();
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    std::cout << "The most Isolated Place is: " << mostIsolatedPlace.name << endl;
    std::cout << "Found in: " << elapsed_secs << " seconds" << endl;
   
}

void measurePerformance(int maxOrderOfMagnitude){
    for(int i=1; i <= maxOrderOfMagnitude ; i++){
        
        int n = pow(10,i);
        
        auto placeCollection = PlaceCollection(n);
        
        
        clock_t begin = clock();
        Place mostIsolatedPlace = placeCollection.mostIsolated();
        clock_t end = clock();
        
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        
       
        cout << "N = " << n  << "\n      Search time:  " << elapsed_secs << "\n      Relative to n log(n) : "  << elapsed_secs/ (n * log(n)) << endl ;
    }
}

int main(int argc, const char * argv[]) {
    
    cout << "Enter the path to a file containing a list of places, hit k to enter places from the keyboard, or m to measure performance on random data." << endl;
    
    string input;
    
    cin >> input;
    
    if(input == "k"){
        cout << "Input places followed by end of file." << endl;
       auto placeCollection = PlaceCollection(cin);
       findMostIsolated(placeCollection);
    }
    else if(input == "m"){
        int ordersOfMagnitude = 6;
        measurePerformance(ordersOfMagnitude);
    }
    else {
        //The input should be a file path
        ifstream inputFile;
        
        inputFile.open(input);
        
        if (!inputFile) {
            cerr << "Unable to open file";
            exit(1);
        }
        
        auto placeCollection = PlaceCollection(inputFile);
        findMostIsolated(placeCollection);
    }
 
    return 0;
}
