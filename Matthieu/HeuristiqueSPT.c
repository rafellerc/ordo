//int (*Heuristic)(int**,int*,int*,int,int)
#include "HeuristiqueSPT.h"
int SPT(int** duree,int* h,int* H,int N_JOBS,int N_MACHINES){

    //op courante pour chaque tache -> init a 0 = machine courante pour tache i
    int* M=calloc(N_JOBS,sizeof(int));

    //date de fin sur machine j -> init a 0
    int* fM=calloc(N_MACHINES,sizeof(int));
    

    //date de fin tache i ->init a 0
    int* C=calloc(N_JOBS,sizeof(int));


    int nbOperationsTraitees;
    for(nbOperationsTraitees=0;nbOperationsTraitees<((N_JOBS) * (N_MACHINES)); nbOperationsTraitees++){
        //on cherche l'operation courante de durée min
		int dureeMin=_infinity;
		int jMin=-1;
		int tmp_i=0;
		for(tmp_i=0;tmp_i<N_JOBS;tmp_i++){
			if(M[tmp_i]<N_MACHINES){ //si toutes les operations de la tache tmp_i n'ont pas etee traitees
				if(dureeMin>duree[tmp_i][M[tmp_i]]){
					dureeMin=duree[tmp_i][M[tmp_i]];
					jMin=tmp_i;
				}
			}
		}
		if(jMin==-1){//pas de plus petite tache courante
			printf("ERROR: pas d'op de duree min trouvee\n");
			exit(1);
		}
		int fin;	
		if(fM[M[jMin]] >= C[jMin]){
			//On regarde si on peut placer l'operation avant l'interruption ou pas
			if(fM[M[jMin]]+dureeMin<=h[M[jMin]]){//on peut placer la tache avant l'interruption
				fin=fM[M[jMin]]+dureeMin;
			}
			else{//on ne peut pas placer la tache avant l'interruption
				if(fM[M[jMin]]>=H[M[jMin]]){//si on a deja place une operation apres l'interruption
					fin=fM[M[jMin]]+dureeMin;
				}
				else{
					fin=H[M[jMin]]+dureeMin;
				}
			}
		}
		else{// fM[M[jMin]] < C[jMin]
			//On regarde si on peut placer l'operation avant l'interruption ou pas
			if(C[jMin]+dureeMin<=h[M[jMin]]){//on peut placer la tache avant l'interruption
				fin=C[jMin]+dureeMin;
			}
			else{//on ne peut pas placer la tache avant l'interruption
				if(C[jMin]>=H[M[jMin]]){//si la date de fin de l'op precedente est apres l'interruption
					fin=C[jMin]+dureeMin;
				}
				else{
					fin=H[M[jMin]]+dureeMin;
				}
			}
		}
		fM[M[jMin]]=fin;
		C[jMin]=fin;
		M[jMin]++;
		
		
		printf("On place op %d du job %d -> date fin: %d\n",M[jMin]-1,jMin,fin);	
    }
    
    int valObj=0;
    {
        int i;
        for(i=0;i<N_JOBS;i++){
            valObj+=C[i];
        }    
    }


    free(C);

    free(fM);

    free(M);

    return(valObj);

}
