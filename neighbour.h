//
// Created by Nathan on 4/22/2022.
//

#ifndef ASTARPROJECT_NEIGHBOUR_H
#define ASTARPROJECT_NEIGHBOUR_H

#include "city.h"


//typedef struct city C;

typedef struct neighbour {
    cityPtr neighbourCity; //ptr to the direct neighbouring city
    int cityDistance; //Distance to the city


}neighbour;

//prints out the name of the neighbour
void displayNeighbour(neighbour *); 

int calcDistance(neighbour* n1, neighbour* n2);

//find and return an array(pointer) of neighbouring city to a specific city
//read as argument the list of neigbours to a city
neighbour* getNeighbourPtr(List* lst, char* n, int dt);

// add neighbours from file to their corresponding city. and add them to the list of neighbours inside the city struct
status addNeighboursTocity(List* lst, char* fp, cityPtr curCity);

//get neighbours from each city inside the list.
void getCityNeighbours(List* list, char* fp); 





#endif //ASTARPROJECT_NEIGHBOUR_H
