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

int heuristique_NEH(InstanceFlowShop* );

int returnMin(int a,int b);

int max(int,int);

int min(int,int);

Job * swapJobs(Job *, int, int, int);

int getSumCiPartial(Job *, int, int *, int *);
