#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int totalDuration;
	int opDurations[3];
	int operationStartTime[3];
	int index;
	float gupta;
}Job;

int compare(const void *, const void *);

int isCollisional(int ,int ,int ,int );

int heuristique_gupta(InstanceFlowShop* );

int returnMin(int a,int b);

int max(int,int);

