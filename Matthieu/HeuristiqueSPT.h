#ifndef _infinity
	#define _infinity 1000000
#endif

int SPT(int** durees,int* h,int* H,int N_JOBS,int N_MACHINES);
int max(int a, int b){
    if(a>=b) return a;
    else
        return b;
}

void pArray(int* array, int size){
    int i;
    
    printf("[");
    
    for(i=0;i<size;i++){
        
        printf("%d, ",array[i]);
        
    }
    printf("]");
    
    
}
