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
#include <cmath>

#include "PlacesCollection.hpp"

/*
     Finds the most isolted place in a PlaceCollection and prints result and search time to the command line.
*/
void findMostIsolated(PlaceCollection placeCollection) {
    clock_t begin = clock();
    Place mostIsolatedPlace = placeCollection.mostIsolated();
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    std::cout << "The most Isolated Place is: " << mostIsolatedPlace.name << std::endl;
    std::cout << "Found in: " << elapsed_secs << " seconds." << std::endl;
   
}

/*
     Measures performance on random data and compares to n log n.
     Prints results to the command line.
     Tests on increasing orders of magnitude up to maxOrderOfMagnitude.
*/
void measurePerformance(int maxOrderOfMagnitude){
    
    for(int i=1; i <= maxOrderOfMagnitude ; i++){
        
        int n = pow(10,i);
        std::cout << "N = " << n  << ":" << std::endl;
        auto placeCollection = PlaceCollection(n);
        
        clock_t begin = clock();
        Place mostIsolatedPlace = placeCollection.mostIsolated();
        clock_t end = clock();
        
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        
        std::cout << "      Search time:  " << elapsed_secs << "\n      Relative to n log(n) : "  << elapsed_secs/ (n * log(n)) << std::endl ;
    }
}

int main(int argc, const char * argv[]) {
    
    std::cout << "Enter the path to a file containing a list of places, or  hit k to enter places from the keyboard or m to measure performance on random data." << std::endl;
    
    std::string input;
    
    std::cin >> input;
    
    if(input == "k"){
        std::cout << "Input places followed by end of file." << std::endl;
        auto placeCollection = PlaceCollection(std::cin);
        findMostIsolated(placeCollection);
    }
    else if(input == "m"){
        int ordersOfMagnitude = 6;
        measurePerformance(ordersOfMagnitude);
    }
    else {
        //The input should be a file path
        std::ifstream inputFile;
        
        inputFile.open(input);
        
        if (!inputFile) {
            std::cerr << "Unable to open file";
            exit(1);
        }
        
        auto placeCollection = PlaceCollection(inputFile);
        findMostIsolated(placeCollection);
    }
 
    return 0;
}
