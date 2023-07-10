/*Group members: 
Betche Nathan Stephane
Praveenkumar reddy karnatam
Jatin Kant

*/

#include <stdlib.h>
#include<stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_DEPRECATE

#include "status.h"
#include "city.h"
#include "neighbour.h"
#define MAXLINE 100

int stringComparator(void *a, void *b) { //follows the strcmp() prototypes
    if (strcmp(a, b) < 0) return -1;
    else if (strcmp(a, b) > 0) return 1;
    else return 0;
}
/*
status success(cityPtr S, cityPtr G) {
    if (S == G)
    {
        printf("Success!! Shortest path found\n");
        while (S)
        {
            printf("%s<-- ", S->name);
            S = S->link;
        }
        return OK;

    }
}

void finder(cityPtr S, int* dt) {
    Node* tmp = S->neighbours->head;
    while (tmp)
    {
        neighbour* neightmp = tmp->val;
        cityPtr successor = neightmp->neighbourCity;
        int distance = neightmp->cityDistance;
        *(dt) = S->gCost + distance;

    }
}
*/
int main() {
    FILE* file;
    
    int nitem = 0;
    int n, _latitude, _longitude;
    
    char _cityName[MAXLINE] = "";
    char start[MAXLINE] = "";
    char destination[MAXLINE] = "";

    
    file = fopen("FRANCE.MAP", "r");

    cityPtr _city;

    List* open;
    List* closed;
    cityPtr startingCity_cityPtr;
    cityPtr destinationGoal_cityPtr;


    

    List* cityList = newList(stringComparator, displayCity);
    if (file != NULL) {

        while ((n = fscanf(file, "%s %d %d", _cityName, &_latitude, &_longitude)) != -1)
        {
            
            if (n == 3)
            {
                
                _city = newCity(_cityName,&_latitude,&_longitude);
                if (!_city)return ERRALLOC;
                addList(cityList, _city);
      
            }
         //   printf("%d \n", n);
                       
        }

        fclose(file);
    }
    else {
        //printf("Failed");
        return ERROPEN;
    }
    fclose(file);

    getCityNeighbours(cityList, "FRANCE.MAP");
    displayList(cityList); 
    
   open = newList(calcGcost, displayCity);
   
    closed = newList(stringComparator, displayCity);

    printf(" /****city names follows the Camel case convention. e.g(Paris, Caen) *******/ \n ");
    printf("\n");
    printf("enter the starting city: ");
    scanf("%[^\n]%*c", start);

    printf("enter the destination point: ");
    scanf("%[^\n]%*c", destination);
    printf("\n");





    startingCity_cityPtr = getCity(cityList,start);
    destinationGoal_cityPtr = getCity(cityList,destination);
    
    startingCity_cityPtr->gCost = 0; // sets the inital or starting city g cost to 0
    startingCity_cityPtr->hCost = hcost(startingCity_cityPtr, destinationGoal_cityPtr);
    addList(open, startingCity_cityPtr);
   // printf("H cost is %d", startingCity_cityPtr->hCost);
    while (open->head)
    {
        void* el;
        int distanceParcouru;
        remFromListAt(open, 1, &el);
        addList(closed, el);
        cityPtr ct = (cityPtr)el;

        Node* tmp = ct->neighbours->head;
        while (tmp)
        {
            neighbour* neightemp = tmp->val;
            cityPtr successor = neightemp->neighbourCity;
            int dst = neightemp->cityDistance;
            distanceParcouru = ct->gCost + dst;
            
            
            if ((isInList(open, successor) != 0) || ((isInList(closed, successor) != 0) && (distanceParcouru > successor->gCost)))
            {
                
                tmp = tmp->next;
                
                
            }
            else {
                if (isInList(open, successor) != 0) remFromList(open, successor);
                if (isInList(closed, successor) != 0) remFromList(closed, successor);

                successor->gCost = distanceParcouru;
                successor->link = ct;
                addList(open, successor);
                tmp = tmp->next;
                
            }
           
        }

        if (ct == destinationGoal_cityPtr) {
            printf("Success!! shortest path found for %s to %s \n from (destination <-- Start)\n",start,destination);
            while (ct)
            {
                printf("%s<--", ct->name);
                ct = ct->link;

            }
            return 0;
        }
      //  success(ct, destinationGoal_cityPtr);
        //--
        
    }
   // printf("Failure");




    return 0;
}
