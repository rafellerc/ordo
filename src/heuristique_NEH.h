#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int totalDuration;
	int opDurations[3];
	int operationStartTime[3];
	int index;
}Job_NEH;

int compare(const void *, const void *);

int isCollisional(int ,int ,int ,int );

int heuristique_NEH(int** durees,int* h,int* H,int N_JOBS,int N_MACHINES);

int returnMin(int a,int b);

int max_NEH(int,int);

int min(int,int);

Job_NEH * swapJobs(Job_NEH *, int, int, int);

int getSumCiPartial(Job_NEH *, int, int *, int *);
