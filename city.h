#ifndef ASTARPROJECT_CITY_H
#define ASTARPROJECT_CITY_H

#include "List.h"

typedef struct neighbour neighbour;

typedef struct city {
    char name[20]; // or char name[x] with x <20
    int latitude, longitude;
    
    
   // int gCost, hCost, fCost;
    int gCost; //*
    int hCost; //*

    List* neighbours;
    struct city* link; //bkctrackCity

}City, *cityPtr;

void displayCity(cityPtr); //displays the city details and its neighbours

cityPtr getCity(List* list, char* cityName);// returns a pointer to the city name passed by argument.

cityPtr newCity(char* n, int *lt, int *lg);

int calcGcost(cityPtr ct1, cityPtr ct2);

int hcost(cityPtr ct1, cityPtr ct2);



#endif //ASTARPROJECT_CITY_H
