/* Onomateponymo: Aris Grigoropoulos
   AM: 1115201800036
*/
#ifndef __TSEvr__
#define __TSEvr__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct data {
        /*  members for airport data in array */
	int AirID;
	char * name;
	char * city;
	char * country;
	char IATA[4];
	char ICAO[5];
	int inCounter;
	int outCounter;
} TStoixeiouEvr;

int TSEvr_setValue (TStoixeiouEvr *target, TStoixeiouEvr source);

int TSEvr_readValue (FILE *from,  TStoixeiouEvr *Elem);

int TSEvr_writeValue(FILE *to, TStoixeiouEvr Elem);

#endif
