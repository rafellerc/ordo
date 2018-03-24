#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// typedef struct{
// 	int totalDuration;
// 	int opDurations[3];
// 	int operationStartTime[3];
// 	int index;
// }Job;

int compare_XUE(const void *, const void *);

int isCollisional_XUE(int ,int ,int ,int );

int heuristique_1(int** durees,int* h,int* H,int N_JOBS,int N_MACHINES);

// int max(int,int);
