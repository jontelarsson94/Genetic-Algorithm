//
//  City.cpp
//  TravelingSalesman
//
//  Created by Jonathan Larsson on 2017-02-07.
//  Copyright © 2017 Jonathan Larsson. All rights reserved.
//

#include <stdio.h>

class City {
public:
    int id;
    int x;
    int y;
    
    City(int id, int x, int y)
    {
        this->id = id;
        this->x = x;
        this->y = y;
    }
};
