/* Onomateponymo: Aris Grigoropoulos
   AM: 1115201800036
*/
#ifndef __Evr__
#define __Evr__

#include <stdlib.h>
#include <stdio.h>
#include "TSEvr.h"
#include "TSDDA.h"
#include "BST/ch8_BSTpointer.h"

typedef struct EvrNode *EvrPtr;

EvrPtr EvrConstruct(int MaxSize);	/* gia erwthma 1 */
int EvrDestruct(EvrPtr *E);		/* gia erwthma 5 */

int EvrInsert(EvrPtr E, TStoixeiouEvr Data); /* gia erwthma 2 */
int EvrSearch(EvrPtr E, keyType key, int InOut, int * found); /* gia erwthma 3 */
int EvrPrintAll(EvrPtr E, FILE *out, int *counter); /* gia Erwthma 4 */
int EvrPrintAllRec(EvrPtr E, FILE *out, typos_deikti a, int *counter); /* gia Erwthma 4 */

#endif
