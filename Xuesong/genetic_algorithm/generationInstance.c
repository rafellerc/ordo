#include "generationInstance.h"

InstanceFlowShop* ExampleCreate(int N_JOBS){
    srand(time(NULL));
    int N_MACHINES=3;//3 machines imposées

    int compteurJobs;
    int** durees= malloc(N_JOBS*N_MACHINES*sizeof(int));
    for(compteurJobs=0;compteurJobs<N_JOBS;compteurJobs++){

        durees[compteurJobs]=malloc(N_MACHINES* sizeof(int));

        int compteurMachine;
        for(compteurMachine=0;compteurMachine<N_MACHINES;compteurMachine++){
            durees[compteurJobs][compteurMachine]=rand()%20;
        }

    }
		
    int* h;
    {
        h=malloc(N_MACHINES*sizeof(int));
	    int compteurMachine;
        for(compteurMachine=0;compteurMachine<N_MACHINES;compteurMachine++){
            h[compteurMachine]=rand()%10;
        }
    }
    int* H;
    {
        H=malloc(N_MACHINES*sizeof(int));
	    int compteurMachine;
        for(compteurMachine=0;compteurMachine<N_MACHINES;compteurMachine++){
            H[compteurMachine]=h[compteurMachine]+rand()%5;
        }
	}
	
    return GEN(N_JOBS,N_MACHINES,durees,h,H);
}

