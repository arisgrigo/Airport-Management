/* Onomateponymo: Aris Grigoropoulos
   AM: 1115201800036
*/
#include "Evretirio.h"

#define Simple 1 /* 0 for AVL - any Evr integer for Simple  */

/* Oi diafores tvn ylopoihsevn Simple kai AVL einai mikres - mporeite na xrhsimopoihsete 
   thn  domh #if ... #else ...#endif gia na diaforopihsete tis dyo ylopoihseis  */
   
#if (Simple)
#include "BST/ch8_BSTpointer.h" /* gia Simple Ylopoihsh */
#else
#include "AVL/ch8_AVLpointer.h" /* gia AVL Ylopoihsh */
#endif


struct EvrNode{
       TStoixeiouEvr *DataArray; /* array of size MaxSize */
       int Index;              /* index of first available element in array */
       typos_deikti TreeRoot;     /* Root of DDA */
} EvrNode;

EvrPtr EvrConstruct(int MaxSize){
/* Oi diafores tvn ylopoihsevn Simple kai AVL einai mikres - 
	mporeite na xrhsimopoihsete thn  domh #if ... #else ...#endif */
   EvrPtr E = malloc(sizeof(EvrNode));			//allocating memory for Evretirio node
   typos_deikti TreeRoot;
#if (Simple)
   printf("use simple BST\n");
   Tree_dimiourgia(&TreeRoot);
#else   
    printf("use AVL BST\n");
    AVLTree_dimiourgia(&TreeRoot);
#endif

	E->DataArray = malloc(MaxSize * sizeof(TStoixeiouEvr));		//allocating memory for every element of the Data array
	E->Index = 0;							//starting with 0 since no data has been inserted yet
	E->TreeRoot = TreeRoot;
	
	printf("Evretirio created!\n");

	return E;
}

int EvrInsert(EvrPtr E, TStoixeiouEvr Data){ 
	TStoixeiouEvr newElem;			//new Element for the Data array
	TStoixeiouDDA newDDAElem;		//new Element for the DDA Tree
	int error = 0;

	TSEvr_setValue(&newElem, Data);		//Copying the data from what was given to the element that we'll put in the data array
	E->DataArray[E->Index] = newElem;	//putting the new data in the data array

	newDDAElem.key = Data.AirID;		//Copying key and index to the new DDA Tree element
	newDDAElem.arrayIndex = E->Index++;
#if (Simple)
	Tree_eisagogi(&(E->TreeRoot),newDDAElem, &error);
#else
	int ypsilotero;
	AVLTree_eisagogi(&(E->TreeRoot),newDDAElem,&ypsilotero, &error);
#endif
	if(error)
		printf("There was a problem while inserting!\n");
	return error;	

}

int EvrSearch(EvrPtr E, keyType key, int InOut, int * found){ 
	TStoixeiouDDA stoixeio;
	typos_deikti deiktis;

	stoixeio.key = key;
#if (Simple)
	Tree_anazitisi(E->TreeRoot, stoixeio, &deiktis, found);
	Tree_periexomeno(deiktis, &stoixeio);			//in order to find correct array index and increase in/out counter
#else
	AVLTree_anazitisi(E->TreeRoot, stoixeio, &deiktis, found);
	AVLTree_periexomeno(deiktis, &stoixeio);
#endif
	if(found){
		if(InOut)
			E->DataArray[stoixeio.arrayIndex].inCounter++;
		else E->DataArray[stoixeio.arrayIndex].outCounter++;
	}
	return 0;
}


int EvrPrintAll(EvrPtr E, FILE *out, int * counter){
typos_deikti a=E->TreeRoot;
int error = 0;

/* endo-diadromh - use recursion with apaidi-depaidi */ 
/* example of use */
#if (Simple)
	error = EvrPrintAllRec(E, out, a, counter);		//a recursive function is necessary for In-Order tree traversal
	if(!error)
		printf("Something went wrong while printing!\n");
#else   
    a=AVLTree_apaidi(a);
#endif

	return error;
}


int EvrPrintAllRec(EvrPtr E, FILE *out, typos_deikti a, int * counter){


	if( a == NULL)
		return 1;

	TStoixeiouDDA	tempDDAElem;			//used to find correct array Index, in order to print elements from the Data array
	int error = 0;

	EvrPrintAllRec(E, out, Tree_apaidi(a), counter);		//In-Order Traversal
	Tree_periexomeno(a, &tempDDAElem);
	error = TSEvr_writeValue(out, E->DataArray[tempDDAElem.arrayIndex]);
	(*counter)++;
	
	EvrPrintAllRec(E, out, Tree_dpaidi(a), counter);

	return error;
}
int EvrDestruct(EvrPtr *E){

#if (Simple)
	Tree_katastrofi(&((*E)->TreeRoot));
#else
	AVLTree_katastrofi(&((*E)->TreeRoot));
#endif
	for(int i = 0; i < (*E)->Index - 1; i++){

		free((*E)->DataArray[i].name);
		free((*E)->DataArray[i].city);			//free the space allocated when inserting the elements
		free((*E)->DataArray[i].country);
	}

	free((*E)->DataArray);
	free(*E);
	*E = NULL;
	printf("Evretirio destroyed!\n");
return 1;}
