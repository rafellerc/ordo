//librairies standard
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generationInstance.c"

#include "heuristique_gupta.c"

typedef int (*Heuristic)(int**,int*,int*,int,int);

//Prototypes
int heuristicTEST(int**,int*,int*,int,int);

void printARRAY(int**,int,int);
InstanceFlowShop* Example1();
