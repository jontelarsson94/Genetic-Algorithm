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

class Initializer {
public:
    int** initializeIndividuals(int numberOfCities)
    {
        srand (time(NULL));
        int** ary = new int*[numberOfCities+1];
        for(int i = 0; i < numberOfCities; ++i){
            ary[i] = new int[numberOfCities+1];
        }
    
        for(int i = 0; i < numberOfCities; i++) {
            for(int j = 0; j < numberOfCities; j++) {
                ary[i][j] = j+1;
            }
            for(int j = 0; j < numberOfCities; j++) {
                int pos1 = rand() %  numberOfCities;
                int pos2 = rand() %  numberOfCities;
                int hold = ary[i][pos1];
                ary[i][pos1] = ary[i][pos2];
                ary[i][pos2] = hold;
            }
        }
        return ary;
    }
    
};
