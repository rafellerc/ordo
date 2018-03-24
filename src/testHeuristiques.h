//librairies standard
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generationInstance.c"
#include "HeuristiqueSPT.c"
#include "heuristique_NEH.c"
#include "heuristique_gupta.c"
#include "heuristique_1.c"
#include "GA.c"

typedef int (*Heuristic)(int**,int*,int*,int,int);

//Prototypes
int heuristicTEST(int**,int*,int*,int,int);

void printARRAY(int**,int,int);
InstanceFlowShop* Example1();
