#include "instanceFlowShop.h"

void F(int N,int M,int** durees,int* h,int* H){
    int i;
    for(i=0;i<N;i++){
        free(durees[i]);
        
    }
    free(h);
    free(H);
    free(durees);
}

InstanceFlowShop* GEN(int N,int M,int** durees,int* h,int* H){
    InstanceFlowShop* INS=malloc(sizeof(InstanceFlowShop));
    (*INS).N_JOBS      =N;
    (*INS).N_MACHINES  =M;
    (*INS).durees      =durees;
    (*INS).h           =h;
    (*INS).H           =H;
    (*INS).F           =&F;        

    return INS;
    

}
