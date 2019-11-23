/* Onomateponymo: Aris Grigoropoulos
   AM: 1115201800036
*/
#include "TSEvr.h"



int TSEvr_setValue (TStoixeiouEvr *target, TStoixeiouEvr source){
	*target = source;

	return 0;
}

int TSEvr_readValue (FILE *from,  TStoixeiouEvr *Elem){
	int error, ID;	
	char name[150];
	char city[100];
	char country[100];
	char IATA[4];
	char ICAO[5];

	fscanf(from, "%d",&ID);
	fgetc(from);
	fscanf(from, "%[^;]s", name);
	fgetc(from);
	fscanf(from, "%[^;]s", city);
	fgetc(from);
	fscanf(from, "%[^;]s", country);		//traversing the line and getting every element (disregarding ";")
	fgetc(from);
	fscanf(from, "%[^;]s", IATA);
	fgetc(from);
	error = fscanf(from, "%s", ICAO);

	Elem->name = malloc(150 *sizeof(char));		//allocating memory for data not yet allocated
	Elem->city = malloc(100 *sizeof(char));
	Elem->country = malloc(100 *sizeof(char));

	Elem->AirID = ID;
	strcpy(Elem->name, name);
	strcpy(Elem->city, city);
	strcpy(Elem->country, country);			//assigning every element into the struct which we'll insert in the array
	strcpy(Elem->IATA, IATA);
	strcpy(Elem->ICAO, ICAO);
	//printf("%d:%s:%s:%s:%s:%s\n",Elem->AirID, Elem->name, Elem->city, Elem->country, Elem->IATA, Elem->ICAO);
	Elem->inCounter = 0;
	Elem->outCounter = 0;

	return error;
}

int TSEvr_writeValue(FILE *to, TStoixeiouEvr Elem){
	int error = 0;

	error = fprintf(to, "Air.ID: %d,	Arrivals: %d,	Departures: %d\n", Elem.AirID, Elem.inCounter, Elem.outCounter);

	return error;
}

