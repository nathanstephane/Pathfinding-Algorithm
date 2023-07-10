
#include "neighbour.h" //neighbour.h already includes city.h
#include <stdio.h>
#include <string.h>
//displays the city details and its neighbours
void displayCity(cityPtr c) {
	printf("\n%s has %d Neighbours\t", c->name, c->neighbours->nelts);
	printf("\n");
	forEach(c->neighbours, displayNeighbour); //toDo create neighbour displayer


}

/*----------------------------------------------------------------------------------------------*/

// returns a pointer to the city name passed by argument.
cityPtr getCity(List* list, char* cityName) {
	//check if list empty
	if (!list->head) return NULL;
	Node* tmp = list->head;
	while (tmp)
	{
		cityPtr c = tmp->val;
		if (strcmp(c->name, cityName) == 0) {
			return tmp->val; //city found
		}
		/*else
		{
			printf("\nCity Name not found. Please make sure you typed in the name correctly");
			return 0;
		}*/
		tmp = tmp->next;
	}
	return 0;

}
/*----------------------------------------------------------------------------------------------*/
//acts as a constructor to create a new city
//param n name of the city
//param lt int* latitude
//param lg int* longitude
//return pointer to City
cityPtr newCity(char* n, int *lt, int *lg) {
	
	cityPtr nCity = (City*)malloc(sizeof(City));  //new city
	if (!nCity) return 0;
	
	strcpy(nCity->name, n);
	nCity->latitude = *(lt);
	nCity->longitude = *(lg);
	nCity->neighbours = newList(calcDistance, displayCity);
	nCity->gCost = 5000;
	nCity->link = 0;

	
	return nCity;

}

/*----------------------------------------------------------------------------------------------*/
//returns the distance cost between two cities
int calcGcost(cityPtr ct1, cityPtr ct2) {
	return ct1->gCost - ct2->gCost;
}

/*----------------------------------------------------------------------------------------------*/
//returns the h cost between two cities based off the pythagoras theorem
int hcost(cityPtr ct1, cityPtr ct2) {
	return ((abs(ct1->latitude - ct2->latitude) + abs(ct1->longitude - ct2->longitude))/4);
}

