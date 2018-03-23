#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int totalDuration;
	int opDurations[3];
	int operationStartTime[3];
	int index;
}Job;

int compare(const void *, const void *);

int isCollisional(int ,int ,int ,int );

int heuristique_1(InstanceFlowShop* );

int max(int,int);
