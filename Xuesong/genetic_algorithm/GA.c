#include "GA.h"


//the compare function is created to sort the population with their fitness.
int compare(const void *a, const void *b){
    return (*(Chrom *)a).fit > (*(Chrom *)b).fit?1:-1;
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

void allocateChrom(Chrom *chrom, int jobNum, InstanceFlowShop* ex) {
    chrom->bits = malloc(jobNum * sizeof(short));
    chrom->fit = 0;
    chrom->ex = ex;
    calFitness(chrom);
}

void initChrom(Chrom *chrom){
	int random;
	int jobNum = chrom->ex->N_JOBS;
	int* randomList = malloc(jobNum * sizeof(int));
	for(int i = 0;i < jobNum;i++){
		randomList[i] = i;
	}
	for(int j = 0;j < jobNum - 1;j++){  
        int m = rand() % jobNum;  
        int n = rand() % jobNum;  
        int k;  
        k = randomList[m];  
        randomList[m] = randomList[n];  
        randomList[n] = k;  
    } 
    for(int i = 0;i < jobNum;i++){
    	chrom->bits[i] = randomList[i];
    }
    
    calFitness(chrom);
}

Chrom* crossover(Chrom* par1, Chrom* par2, int len){
	int random;
	random = rand();
	random = random % (len - 1) + 1;  //get the crossover point
	static Chrom childrens[2];
	allocateChrom(childrens + 0, len, par1->ex);
	allocateChrom(childrens + 1, len, par1->ex);
	for(int i = 0;i < random;i++){
		childrens[0].bits[i] = (*par1).bits[i];
		childrens[1].bits[i] = (*par2).bits[i];
	}
	
	int k1 = 0;
	int k2 = 0;
	for(int i = 0; i < len;i++){
		int flag1 = -1;
		int flag2 = -1;
		
		for(int j = 0;j < random;j++){
			if((*par2).bits[i] == childrens[0].bits[j]){
				flag1 = 1;
			}
				
			if((*par1).bits[i] == childrens[1].bits[j]){
				flag2 = 1;
			}
				
		}
		//printf("%d	%d\n",flag1,flag2);
		//printf("%d	%d\n",k1,k2);
		if(flag1 == -1){
			childrens[0].bits[random + k1] = (*par2).bits[i];
			k1++;
		}
		if(flag2 == -1){
			childrens[1].bits[random + k2] = (*par1).bits[i];	
			k2++;
		}
						
	}
	
//for test	
/*	printf("parents:\n");
	bits(par1,len);
	bits(par2,len);
	printf("childrens:\n");
	bits(childrens,len);
	bits(childrens + 1,len);*/
	
	calFitness(childrens + 0);
	calFitness(childrens + 1);
	
	return childrens;
}


Chrom mutation(Chrom* par, int len){
	Chrom child;
	allocateChrom(&child, len, par->ex);
	short bitTemp;
	int randomBit, randomPos;
	randomBit = rand();
	randomBit = randomBit % len;
	randomPos = rand();
	randomPos = randomPos % len;

	bitTemp = (*par).bits[randomBit];
	for(int i = 0;i < randomBit;i++){
		child.bits[i] = (*par).bits[i];
	}
	for(int i = randomBit;i < len - 1;i++){
		child.bits[i] = (*par).bits[i + 1];
	}

	for(int i = len - 1;i > randomPos;i--)
		child.bits[i] = child.bits[i - 1];

	child.bits[randomPos] = bitTemp;
	calFitness(&child);
	
	return child;
}


// we chose the P_SIZE chroms with lower fit
void selection(Chrom* population){
	qsort((void *)population, 2*P_SIZE, sizeof(Chrom), compare);
	//for(int i = P_SIZE;i < 2*P_SIZE;i++)
	//	population[i] = NULL;
}

void copyChrom(Chrom* destination,Chrom original, int length){
	for(int i = 0;i < length;i++){
		(*destination).bits[i]	= original.bits[i];
	}
	(*destination).fit = original.fit;
}

void calFitness(Chrom* chrom){
	InstanceFlowShop* ex = chrom->ex;
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
		jobOrderList[i].opDurations[0] = ex->durees[(*chrom).bits[i]][0];
		jobOrderList[i].opDurations[1] = ex->durees[(*chrom).bits[i]][1];
		jobOrderList[i].opDurations[2] = ex->durees[(*chrom).bits[i]][2];
		jobOrderList[i].totalDuration = ex->durees[(*chrom).bits[i]][0] + ex->durees[(*chrom).bits[i]][1] + ex->durees[(*chrom).bits[i]][2];
		jobOrderList[i].index = (*chrom).bits[i];
	}

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
	(*chrom).fit = cost;
}

void printBits(Chrom* population,int jobNum,int l){
		printf("the %d iteration\n",l);
	for(int j = 0;j < 2 * P_SIZE;j += 2){
		for(int i = 0;i < jobNum;i++){
			printf("%d ",population[j].bits[i]);
		}
		printf("end fit = %d\n",population[j].fit);
	}
}
void bits(Chrom* chrom,int len){
	printf("bits: ");
    for(int i = 0;i < len;i++){
			printf("%d ",chrom->bits[i]);
		}
	printf("\n");
}



void geneticAlgo(InstanceFlowShop* ex){
	int jobNum = ex->N_JOBS;
	int* h = ex->h;
	int* H = ex->H;
	
	//create a population of P_SIZE, the rest P_SIZE are the childrens.
	Chrom population[2 * P_SIZE];
	for(int i = 0;i < 2 * P_SIZE;i++)
		allocateChrom(&population[i], jobNum, ex);
	for(int i = 0;i < P_SIZE;i++) 
		initChrom(population + i);
	
	
	float p;
	int par1,par2;
	Chrom *twoChilds;
	for(int i = 0;i < ITER_MAX;i++){
		for(int j = 0;j < P_SIZE/2;j++){
			par1 = rand() % P_SIZE;          // choose two parents
			par2 = rand() % P_SIZE;
			if(par1 == par2){
				par2++;
			}
			p = (rand() % 100 + 1) / 100;   // generation a probability  0 <= p <= 1
			if(p <= P_CROSS){
				twoChilds = crossover(&population[par1],&population[par2],jobNum);
				//bits(twoChilds,jobNum);
				//bits(twoChilds + 1,jobNum);
				copyChrom(population + P_SIZE + 2*j + 0,twoChilds[0],jobNum);
				copyChrom(population + P_SIZE + 2*j + 1,twoChilds[1],jobNum);

			}
			else if(p > P_CROSS){
				copyChrom(population + P_SIZE + 2*j + 0,mutation(&population[par1],jobNum),jobNum);
				copyChrom(population + P_SIZE + 2*j + 1,mutation(&population[par2],jobNum),jobNum);
			}
		}
		
		printBits(population,jobNum,i);
		//for (int k = 0; k < 2 * P_SIZE; ++k) printf("%d  ",population[k].fit); printf("before\n");
		selection(population);
		//for (int k = 0; k < 2 * P_SIZE; ++k) printf("%d  ",population[k].fit); printf("after\n");
		printf("the best sumCi: %d\n",population[0].fit);
	}
	
}
