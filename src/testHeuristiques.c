#include "testHeuristiques.h"

int main(int nargs,char** strargs){
	
	Heuristic heuristicsArray[]= {&heuristicTEST,&heuristique_NEH,&SPT,&heuristique_gupta};
	int nJobs=40;
	if(nargs==2)
		nJobs=atoi(strargs[1]);
	
	
    InstanceFlowShop* ex1 = ExampleCreate(nJobs);
    {
        int i;
        if(heuristicsArray[0])
            for(i=0;i<sizeof(heuristicsArray)/sizeof(heuristicsArray[0]);i++){
                printf("Heuristique %d -> val: %d\n",i,heuristicsArray[i](ex1->durees,ex1->h,ex1->H,ex1->N_JOBS,ex1->N_MACHINES));

            }

    }
    (*(ex1->F))(ex1->N_JOBS,ex1->N_MACHINES,ex1->durees, ex1->h, ex1->H);
	


}

int heuristicTEST(int** durees,int* h,int* H,int N_JOBS,int N_MACHINES){

	if(!durees || !h || !H)	return 0;
	//nbr machines
	int M= N_MACHINES;

	//nbr taches
	int N= N_JOBS;

	
	printf("Durees :\n");
	printARRAY(durees,N,M);
	printf("Interruptions:\n");
	int i;
	for(i=0;i<M;i++){
		printf("h_%d: %d -> H_%d: %d \n",i,h[i],i,H[i]);
	}

	return 1;
}



void printARRAY(int** array, int width , int length){
	int i;
	for(i=0;i<width;i++){
		int j;
		for(j=0;j<length;j++){
			printf("%d; ",array[i][j]);
		}	
		printf("\n");
	}

}




