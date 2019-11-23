/************************************************************************
Programma pelaths	: AirportManagement.c
Syggrafeas			: 
Skopos				: skeleton main for askhsh 3
*************************************************************************/
/* Onomateponymo: Aris Grigoropoulos
   AM: 1115201800036
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TSEvr.h"
#include "TSDDA.h"
#include "Evretirio.h"

void insert(EvrPtr E, FILE * data){
	TStoixeiouEvr Elem;
	int ch = fgetc(data), error = 0;
	ungetc(ch,data);		//ungetc because the first character that we read must also be inserted
	while(ch != EOF){
		TSEvr_readValue(data, &Elem);			//read and insert each line
		error = EvrInsert(E, Elem);
		
		if(ch == '\n')					//if at end of line, go to next line
			ch = fgetc(data);
		if(ch == EOF)					//if at end of file, stop
			break;
		ch = fgetc(data);				//check to see if end of file has been reached
		ungetc(ch, data);				//if not, get next char again

	}
	if(error)
		printf("There was a problem while inserting!\n");
	else printf("Elements Inserted!\n");
}

void search(EvrPtr E, FILE *data){			//process used to get keys from routes file and search for them in DDA Tree
	int ch;
	int found = 0, keyOut,keyIn;

	while(ch != EOF){
		if(ch == '\n')
			ch = fgetc(data);			//if at end of line, go to next line
		if(ch != EOF){
			ungetc(ch,data);
			char buf[1800];
			fscanf(data, "%[^;]s", buf);
			fgetc(data);
			fscanf(data, "%[^;]s", buf);
			fgetc(data);
			fscanf(data, "%[^;]s", buf); 
			fgetc(data);
			fscanf(data, "%d", &keyOut);
			fgetc(data);
			fscanf(data, "%[^;]s", buf); 		//traverse each line and get only the 2 numbers that we care about
			fgetc(data);
			fscanf(data, "%d", &keyIn);		//the rest go to a buffer
			fgetc(data);
			fscanf(data, "%[^;]s", buf); 
			fgetc(data);
			fscanf(data, "%[^;]s", buf); 
			fgetc(data);
			fscanf(data, "%[^\n]s", buf); 
		//printf("keyOut:%d, keyIn:%d\n", keyOut, keyIn); 
		}
	
		found = EvrSearch(E,keyOut,0,&found);
		found = EvrSearch(E,keyIn,1,&found);
		ch = fgetc(data);
	}
}

void print(EvrPtr E, FILE *to){				//process used to print every element of the DDA Tree
int counter = 0, error;

error = EvrPrintAll(E, to, &counter);

if(!error)
	printf("There was a problem while printing!\n");
else printf("Total airlines printed:%d!\n",counter);
}

int main(int argc, char *argv[]){
	EvrPtr E;
	FILE * data;

	E=EvrConstruct(7200);				//every process for Randomly sorted txt file

	data = fopen("DATA/Linux/airportsLinuxRandom.txt","r");
	insert(E, data);
	fclose(data);

	data = fopen("DATA/Linux/routesLinux.txt", "r");
	search(E, data);
	fclose(data);

	data = fopen("DATA/Linux/OUTPUTRandomBST.txt", "w");
	print(E, data);
	fclose(data);

	EvrDestruct(&E);

	E=EvrConstruct(7200);				//every process for Sorted txt file

	data = fopen("DATA/Linux/airportsLinuxSorted.txt","r");
	insert(E, data);
	fclose(data);

	data = fopen("DATA/Linux/routesLinux.txt", "r");
	search(E, data);
	fclose(data);

	data = fopen("DATA/Linux/OUTPUTSortedBST.txt", "w");
	print(E, data);
	fclose(data);

	EvrDestruct(&E);
	
	getchar();	
	return 0;
}

