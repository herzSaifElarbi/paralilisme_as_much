#include <stdio.h>
#include <omp.h>

int main() {
    //as number of cpu cores
    #pragma omp parallel
    {
        //printf("Hello \n");
        printf("Hello from thread %d!\n", omp_get_thread_num());
    }
    return 0;
}
//g++ -fopenmp -o hello hello.cpp
//./hello