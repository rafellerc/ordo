typedef void (*freeFct)(int,int,int**,int*,int*);
typedef struct StructFlowShop {
    int N_JOBS;
    int N_MACHINES;
    int** durees;
    int* h;
    int* H;
    freeFct F;
    
} InstanceFlowShop;


