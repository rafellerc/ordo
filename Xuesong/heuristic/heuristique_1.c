#include "heuristique_1.h"


int compare(const void *a, const void *b){
    return (*(Job *)a).totalDuration > (*(Job *)b).totalDuration?1:-1;
}

// judge whether an operation has collision with the interruptions, 
// if there is collision, return -1,else return 1.
int notCollisional(int t,int opDuration,int h,int H){
	if(t + opDuration <= h || t >= H)
		return 1;
	else
		return 0;
}

int max(int a,int b){
	if(a > b) return a;
	else return b;
}

void printResult(Job* list,int num){
	printf("Ordonnancement:\n");
	for(int i = 0; i < num;i++){
		printf("the %d th job: ", list[i].index + 1);
		printf("%d %d %d\n", list[i].operationStartTime[0],list[i].operationStartTime[1],list[i].operationStartTime[2]);
	}
}

int heuristique_1(InstanceFlowShop* ex){
	int jobNum = ex->N_JOBS;
	int* h = ex->h;
	int* H = ex->H;
	
	//create a jobList which will be sorted
	Job* jobOrderList = malloc(jobNum*sizeof(Job));
    for(int i = 0;i < jobNum;i++){
        Job jobOrderList[i];
    }

	//give value for every job in joborderList
	for(int i = 0;i < jobNum;i++){
		// ex->durees[i] == NULL
		jobOrderList[i].opDurations[0] = ex->durees[i][0];
		jobOrderList[i].opDurations[1] = ex->durees[i][1];
		jobOrderList[i].opDurations[2] = ex->durees[i][2];
		jobOrderList[i].totalDuration = ex->durees[i][0] + ex->durees[i][1] + ex->durees[i][2];
		jobOrderList[i].index = i;
	}
	
	// sort the jobOrderList
	qsort((void *)jobOrderList, jobNum, sizeof(Job), compare);

	//do the ordonnance for the first machine
	for(int i = 0,t = 0;i < jobNum;i++){
		if(notCollisional(t,jobOrderList[i].opDurations[0],h[0],H[0])){				
			jobOrderList[i].operationStartTime[0] = t;
			t += jobOrderList[i].opDurations[0];
		}
		else{
			jobOrderList[i].operationStartTime[0] = H[0];
			t = H[0] + jobOrderList[i].opDurations[0];
		}
	}

	//do the ordonnance for the second machine
	for(int i = 0,t = 0;i < jobNum;i++){
		t = max(t,jobOrderList[i].operationStartTime[0] + jobOrderList[i].opDurations[0]);
		if(notCollisional(t,jobOrderList[i].opDurations[1],h[1],H[1])){
			jobOrderList[i].operationStartTime[1] = t;
			t += jobOrderList[i].opDurations[1];
		}
		else{
			jobOrderList[i].operationStartTime[1] = H[1];
			t = H[1] + jobOrderList[i].opDurations[1];
		}
	}

	//do the ordonnance for the third machine
	for(int i = 0,t = 0;i < jobNum;i++){
		t = max(t,jobOrderList[i].operationStartTime[1] + jobOrderList[i].opDurations[1]);
		if(notCollisional(t,jobOrderList[i].opDurations[2],h[2],H[2])){
			jobOrderList[i].operationStartTime[2] = t;
			t += jobOrderList[i].opDurations[2];
		}
		else{
			jobOrderList[i].operationStartTime[2] = H[2];
			t = H[2] + jobOrderList[i].opDurations[2];
		}
	}
	
	int cost = 0;
	for(int i = 0;i < jobNum;i++){
		cost += jobOrderList[i].operationStartTime[2] + jobOrderList[i].opDurations[2];
	}
	
	printResult(jobOrderList,jobNum);
	return cost;
	
	
	
	
	
	
}
