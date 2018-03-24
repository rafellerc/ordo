#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "heuristique_1.h"


// typedef struct{
// 	int totalDuration;
// 	int opDurations[3];
// 	int operationStartTime[3];
// 	int index;
// }Job;

// create a chrom structure
typedef struct{
    short int* bits;
    int fit;
		int* h;
		int* H;
		int N_JOBS;
		int** durees;
    // InstanceFlowShop* ex;
}Chrom;
#define ITER_MAX 5
#define P_SIZE 10
#define P_CROSS  0.9 // we define the crossover probability = 0.9
#define P_MUT  0.1   // the mutation probability = 0.1

int geneticAlgo(int** durees,int* h,int* H,int N_JOBS,int N_MACHINES);

int compare_GA(const void *, const void *);
// int isCollisional(int ,int ,int ,int );
// int max(int,int);

void initChrom(Chrom *);
Chrom* crossover(Chrom*, Chrom*,int);
Chrom mutation(Chrom*, int);
void selection(Chrom*);
void calFitness(Chrom*);
void copyChrom(Chrom*,Chrom,int);
void bits(Chrom*,int);
