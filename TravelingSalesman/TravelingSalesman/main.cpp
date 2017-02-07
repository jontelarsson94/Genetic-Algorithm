//
//  main.cpp
//  TravelingSalesman
//
//  Created by Jonathan Larsson on 2017-02-07.
//  Copyright © 2017 Jonathan Larsson. All rights reserved.
//

#include <iostream>
#include "City.cpp"
#include "Initializer.cpp"
using namespace std;

int main(int argc, const char * argv[]) {
    
    Initializer init;
    
    int **ary = init.initializeIndividuals(5);
    
    ary[0] = ary[1];
    
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            cout << ary[i][j] << ", ";
        }
    }
    
    return 0;
}
