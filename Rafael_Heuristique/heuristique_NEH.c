#include "heuristique_NEH.h"

int compare(const void *a, const void *b){
    return (*(Job *)a).totalDuration > (*(Job *)b).totalDuration?1:-1;
}

int max(int a,int b){
	if(a > b)
		return a;
	else
		return b;
}

int min(int a,int b){
	if(a > b)
		return b;
	else
		return a;
}

Job * swapJobs(Job* jobList, int pos1, int pos2, int size){
  // Swaps the elements in positions pos1 and pos2. Returns a new jobList
  Job * newList = malloc(size*sizeof(Job));
  for(int i=0; i<size; i++){
    newList[i] = jobList[i];
  }
  newList[pos1] = jobList[pos2];
  newList[pos2] = jobList[pos1];
  return newList;
}


int heuristique_NEH(InstanceFlowShop* ex){
  int opt;
  int jobNum = ex->N_JOBS;
  int* h = ex->h;
  int* H = ex->H;

  Job* jobOrderList = malloc(jobNum*sizeof(Job));
  // for(int i = 0;i < jobNum;i++){
  //       Job jobOrderList[i];
  //   }
  for(int i = 0;i < jobNum;i++){
  		// ex->durees[i] == NULL
  		jobOrderList[i].opDurations[0] = ex->durees[i][0];
  		jobOrderList[i].opDurations[1] = ex->durees[i][1];
  		jobOrderList[i].opDurations[2] = ex->durees[i][2];
  		jobOrderList[i].totalDuration = ex->durees[i][0] + ex->durees[i][1] + ex->durees[i][2];
  		jobOrderList[i].index = i;
  	}

  // Prints the original sumCi to let you compare with the algorithm
  printf("Original non-ordered sumCi: %d\n",getSumCiPartial(jobOrderList,jobNum,h,H));

  // Orders the Jobs in increasing order of totalDuration
  qsort((void *)jobOrderList, jobNum, sizeof(Job), compare);

  printf("List ordered in increasing order of totalDuration\n");
  for(int k=0; k<jobNum; k++)
    printf("%d\n",jobOrderList[k].index);

  printf("Ordered sumCi: %d\n",getSumCiPartial(jobOrderList,jobNum,h,H));

  for(int i = 1; i < jobNum; i++){
    // sumCi is the array that contains the sumCi for each of the permutations
    int sumCi[i+1];
    Job Permut[i+1][jobNum];
    for(int k = 0; k<jobNum; k++){
    // Copies the content of the original OrderList to the first permutation
      Permut[0][k] = jobOrderList[k];
      }


    sumCi[0] = getSumCiPartial(Permut[0],i+1,h,H);

    for(int j = 1; j < i+1; j++){
      // Permutes without changing the relative position of the already optimised jobs
        Job * swap = swapJobs(Permut[j-1],i-j,i-j+1,jobNum);
        for(int k = 0; k<jobNum; k++){
          Permut[j][k] = swap[k];
        }
        sumCi[j] = getSumCiPartial(Permut[j],i+1,h,H);
    }
    // Finds the permutation with smallest sumCi and discard all others.
    int min_index = 0;
    int min_sumCi = sumCi[0];
    for(int k = 1; k<i+1; k++){
      if(sumCi[k] < min_sumCi){
        min_index = k;
        min_sumCi = sumCi[k];
      }
    }
    opt = min_sumCi;
    for(int k = 0; k<jobNum; k++){
      jobOrderList[k] = Permut[min_index][k];
    }
  }


  printf("List after heuristic\n");
  for(int k=0; k<jobNum; k++)
    printf("%d\n",jobOrderList[k].index);


  return opt;
}

// Calculates the Sum of end dates of each Job taking into account the interruptions
int getSumCiPartial(Job * JobList, int partialSize, int * h, int * H){
  // tEndOp[n] is the end time of operation n in machine n from the last assigned Job
  int tEndOp[3] = {0};
  int SumCi = 0;
  int start_time;

  for(int i = 0; i<partialSize; i++){
    for(int j = 0; j < 3; j++){
      // First set the earliest possible start time, as the minimum between the
      // end of the previous operation and the end of the same op from the previous job
      if(j==0)
        start_time = tEndOp[0];
      else
        start_time = max(tEndOp[j],tEndOp[j-1]);
    // Checks if the interruption happens between the start and end of the operation
    // if so the new end time is the
    if(start_time <= h[j] && JobList[i].opDurations[j] + start_time > h[j])
      tEndOp[j] = H[j] + JobList[i].opDurations[j];
    else
      tEndOp[j] = start_time + JobList[i].opDurations[j];
    // printf("Job %d, Machine %d = %d\n",i,j,tEndOp[j]);
    }
    SumCi += tEndOp[2];
  }
  return SumCi;
}
