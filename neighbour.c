#include "neighbour.h"
#include <stdio.h>

/*-----------------------------------------------------------*/

void displayNeighbour(neighbour* n) {
	
	printf("\t%s  ", n->neighbourCity->name);
	//printf("DISTANCE OR COST TO CITY\n");
	printf("(distance=  %d)", n->cityDistance);
	printf("\n");
}

/*-----------------------------------------------------------*/

//Returns the distance between 2 neighbouring cities
int calcDistance(neighbour* n1, neighbour* n2) {
	return n1->cityDistance - n2->cityDistance;
}

/*-----------------------------------------------------------*/

neighbour* getNeighbourPtr(List* lst, char* name, int dt) {
	Node* tmp; // to find the city inside the linked list
	neighbour* nPtr = (neighbour*)malloc(sizeof(neighbour));
	if (!nPtr) return 0; //or exit(1)
	nPtr->cityDistance = dt;
	tmp = isInList(lst, name);
	if (!tmp) return 0;

	if (tmp == 1) {
		printf("This is weird");
		tmp = lst->head;
		nPtr->neighbourCity = tmp->val;
		return nPtr;
	}
	tmp = tmp->next;
	nPtr->neighbourCity = tmp->val;
	return nPtr;

}

/*-----------------------------------------------------------*/

status addNeighboursTocity(List* lst, char* fp, cityPtr curCity) {
	int latitude, longitude, wordCount, dt;
	char _cityName[30];
	neighbour* ngPtr;
	FILE* file = fopen(fp, "r");
	if (!file) return ERROPEN;
	while ((wordCount = fscanf(file, "%s %d %d", _cityName, &latitude, &longitude)) != -1)
	{
		if (wordCount != 3) continue;
		if (lst->comp(curCity, _cityName) != 0) { continue; }

		do
		{
			wordCount = fscanf(file, "%s %d %d", _cityName, &dt, &longitude);
			if (wordCount == 3 || wordCount == -1) { fclose(file); return OK; }
			ngPtr = getNeighbourPtr(lst, _cityName, dt);
			addList(curCity->neighbours, ngPtr);

		} while (wordCount == 2);
		//--

	//if(!file) return ERROPEN;
	//while (!feof(file))
	//{
	//	wordCount = fscanf(file,"%s %d %d", _cityName, &latitude, &longitude);
	//	if(wordCount != 3) continue;
	//	if(lst->comp(curCity, _cityName) != 0)  //if the city name in the file do not match the city name in the list then we have a neighbour so we skip
	//		continue;
	//	
	//	do
	//	{
	//		wordCount = fscanf(file, "%s %d %d", _cityName, &dt, &longitude);
	//		if (wordCount == 3 || wordCount == -1) { 
	//			fclose(file); 
	//			return OK;
	//		}
	//		ngPtr = getNeighbourPtr(lst,_cityName,dt);
	//		addList(curCity->neighbours, ngPtr);

	//	}while (wordCount == 2);
	
		

	}
	fclose(file);
	return OK;
}

/*-----------------------------------------------------------*/
void getCityNeighbours(List* list, char* fp) {
	
	int n = list->nelts;
	cityPtr curCity;
	for (int i = 1; i < n; i++)
	{
		nthInList(list, i, (void**)&curCity);
		addNeighboursTocity(list, fp, curCity);

	}

}