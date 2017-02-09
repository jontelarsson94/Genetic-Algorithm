//
//  Initializer.cpp
//  TravelingSalesman
//
//  Created by Jonathan Larsson on 2017-02-07.
//  Copyright © 2017 Jonathan Larsson. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <fstream>
#include "City.cpp"
using namespace std;

class Initializer {
public:
    int** initializeIndividuals(int numberOfCities, int populationSize)
    {
        srand (time(NULL));
        int** ary = new int*[populationSize];
        for(int i = 0; i < populationSize; ++i){
            ary[i] = new int[numberOfCities];
        }
    
        for(int i = 0; i < populationSize; i++) {
            for(int j = 0; j < numberOfCities; j++) {
                ary[i][j] = j+1;
            }
            random_shuffle(&ary[i][1], &ary[i][numberOfCities-1]);
        }
        
        return ary;
    }
    
    City* readCitiesFromFile(string fileName, int numberOfCities)
    {
        ifstream infile(fileName);
        City *cities = new City[numberOfCities];
        int id;
        float x, y;
        int i = 0;
        while ((infile >> id >> x >> y) && i < numberOfCities)
        {
            cities[i] = City(id, x, y);
            i++;
        }
        
        return cities;
    }
    
};
