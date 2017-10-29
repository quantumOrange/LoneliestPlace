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
     Finds the most isolated place from an input stream and prints result and search time to the command line.
*/
void findMostIsolated(std::istream &input) {
    auto placeCollection = PlaceCollection(input);
    //PlaceCollection placeCollection
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

bool testMostIsloatedPlace(std::string fileName, std::string expectedResult){
    
    std::ifstream inputFile;
    //"usr/share/man/man1/
    inputFile.open(fileName);
    
    if (!inputFile) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
        //exit(1);
        return false;
    }
    
    auto placeCollection = PlaceCollection(inputFile);
    
    
    Place mostIsolatedPlace = placeCollection.mostIsolated();
    
    bool result = mostIsolatedPlace.name == expectedResult;
    
    if (result) {
        std::cout <<"Test for " << fileName << " data passed. Most isolated place is " << mostIsolatedPlace.name << "." <<  std::endl;
    }
    else {
        std::cout << fileName << " test failed. Most isolated place found (" << mostIsolatedPlace.name <<  ") is not the expected result (" <<  expectedResult << ")."   << std::endl;
    }
    
    return result;
}


int main(int argc, const char * argv[]) {
    
    std::cout << "Enter the path to a file containing a list of places." << std::endl;
    std::cout << "           or  enter k to enter places from the keyboard or m to measure performance on random data." << std::endl;
    std::cout << "           or  enter m to measure performance on random data." << std::endl;
    std::cout << "           or  enter t to run tests." << std::endl;
    
    std::string input;
    
    std::cin >> input;
    
    if(input == "k"){
        std::cout << "Input places followed by end of file." << std::endl;
       
        findMostIsolated(std::cin);
    }
    else if(input == "m"){
        int ordersOfMagnitude = 6;
        measurePerformance(ordersOfMagnitude);
    }
    else if (input == "t") {
        
        bool test1 = testMostIsloatedPlace("problem_small.txt", "place6");
        bool test2 = testMostIsloatedPlace("problem_big.txt", "place55163");
        
        if(test1 && test2){
            std::cout << "All tests passed" << std::endl;
        }
    }
    else {
        //The input should be a file path
        std::ifstream inputFile;
        
        inputFile.open(input);
        
        if (!inputFile) {
            std::cerr << "Unable to open file";
            exit(1);
        }
        
        findMostIsolated(inputFile);
    }
 
    return 0;
}
