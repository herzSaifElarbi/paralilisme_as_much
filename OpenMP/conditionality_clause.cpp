#include <stdio.h>
#include <omp.h>

int main() {
    //as number of cpu cores
    int parallelism_enabled=1;
    #pragma omp parallel for if(parallelism_enabled)
    for(int c=0; c<10; ++c)
        printf("%d with thread :%d \n",c, omp_get_thread_num());
            //printf("Hello from thread %d!\n", omp_get_thread_num());

    
    return 0;
}
//g++ -fopenmp -o conditionality_clause conditionality_clause.cpp
//./conditionality_clause