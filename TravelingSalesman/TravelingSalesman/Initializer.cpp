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
    int** initializeIndividuals(int numberOfCities)
    {
        srand (time(NULL));
        int** ary = new int*[numberOfCities];
        for(int i = 0; i < numberOfCities; ++i){
            ary[i] = new int[numberOfCities];
        }
    
        for(int i = 0; i < numberOfCities; i++) {
            for(int j = 0; j < numberOfCities; j++) {
                ary[i][j] = j+1;
            }
            for(int j = 1; j < numberOfCities; j++) {
                int pos1 = rand() %  numberOfCities-1 + 1;
                int pos2 = rand() %  numberOfCities-1 + 1;
                int hold = ary[i][pos1];
                ary[i][pos1] = ary[i][pos2];
                ary[i][pos2] = hold;
            }
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
        while (infile >> id >> x >> y)
        {
            cities[i] = City(id, x, y);
            i++;
        }
        
        return cities;
    }
    
};
