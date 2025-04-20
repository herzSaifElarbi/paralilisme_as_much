#include <omp.h>    // OpenMP header file
#include <stdio.h>

#define ARRAY_SIZE 1000
#define CHUNK_SIZE 100

int main() {
    int array[ARRAY_SIZE];
    
    // Calculate number of threads based on chunk size
    // We divide the array into CHUNK_SIZE parts, and add 1 to ensure full coverage
    int thread_num = ARRAY_SIZE / CHUNK_SIZE + 1;
    omp_set_num_threads(thread_num); // Set the number of threads to be used

    int i;

    // Initialize the array with values from 0 to ARRAY_SIZE - 1
    for (i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i;
    }

    // Parallel region begins
    // 'for' directive with 'schedule(guided, CHUNK_SIZE)' assigns work dynamically,
    // starting with large chunks, decreasing over time for better load balancing.
    // 'private(i)' ensures each thread has its own local copy of loop variable i.
    #pragma omp parallel for schedule(guided, CHUNK_SIZE) private(i)
    for (i = 0; i < ARRAY_SIZE; i++) {
        int n = array[i];    // Get current value to compute
        int num_of_one = 0;  // Store count of 1s in binary representation

        // Count the number of 1s in the binary representation of n
        // This uses the Brian Kernighan's Algorithm: repeatedly clear the lowest set bit
        if (n != 0) {
            num_of_one++;
            while ((n = n & (n - 1)) != 0) {
                num_of_one++;
            }
        }

        array[i] = num_of_one;  // Store the count back into the array
    }

    // Print the updated array (number of 1s in each index's binary form)
    for (i = 0; i < ARRAY_SIZE; i++) {
        printf("%d => %d \n",i, array[i]);
    }

    printf("\n");
    return 0;  // Fixed: originally was written as return0;
}
//g++ -fopenmp -o calcul_1s_in_binary_in_range calcul_1s_in_binary_in_range.cpp; ./calcul_1s_in_binary_in_range
//calculate number of 1s in binaray format in range 0=>999
