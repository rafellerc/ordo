#include "testHeuristiques.h"


int main(int argc, char* argv[]){
	
	Heuristic heuristicsArray[]= {&heuristicTEST};
	
    InstanceFlowShop* ex1 = ExampleCreate(4);
	heuristicsArray[0](
        ex1->durees,
        ex1->h,
        ex1->H,
        ex1->N_JOBS,
        ex1->N_MACHINES
        
);

	printf("the sum is: %d\n", heuristique_gupta(ex1)); 

	(*(ex1->F))(ex1->N_JOBS,ex1->N_MACHINES,ex1->durees, ex1->h, ex1->H);
	

}

int heuristicTEST(int** durees,int* h,int* H,int N_JOBS,int N_MACHINES){

	if(!durees || !h || !H)	return 0;
	//nbr machines
	int M= N_MACHINES;

	//nbr taches
	int N= N_JOBS;

	printf("\n%lu: %d x %d\n",sizeof(durees),M,N);
	printf("Durées :\n");
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
/*
InstanceFlowShop* Example1(){
    int N_JOBS=4;
	int N_MACHINES=3;
	int** durees= malloc(N_JOBS*N_MACHINES*sizeof(int));
	{
		int temp[]={2,3,6};
		durees[0]=intdup(temp, sizeof(temp));
	}
	{
		int temp[]={3,2,1};
		durees[1]=intdup(temp, sizeof(temp));
	}
	{
		int temp[]={5,4,7};
		durees[2]=intdup(temp, sizeof(temp));
	}
	{
		int temp[]={8,9,2};
		durees[3]=intdup(temp, sizeof(temp));
	}	
    int* h;
    {
        int temp[]={4,6,4};
	    h=intdup(temp,sizeof(temp));
    }
    int* H;
    {
        int temp[]={5,7,9};
	    H=intdup(temp,sizeof(temp));
	}
	
    return GEN(N_JOBS,N_MACHINES,durees,h,H);
}*/

