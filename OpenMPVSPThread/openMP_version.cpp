#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 100                  // Size of the warehouse buffer
#define THREAD_NUM_WORKER 15     // Number of worker threads
#define THREAD_NUM_CONSUMER 10   // Number of consumer threads
#define SLEEP_WORKERS 2          // Delay for worker threads
#define SLEEP_CONSUMERS 1        // Delay for consumer threads

int warehouse[SIZE];             // Shared buffer array
int at = -1;                     // Index of the top element in warehouse (stack-like behavior)
int is_end = 0;                  // Flag to signal end of processing

// Function to simulate workers producing items
void start_workers()
{
    // Set number of OpenMP threads for workers
    omp_set_num_threads(THREAD_NUM_WORKER);

    // Parallel region for worker threads
    #pragma omp parallel default(shared)
    {
        if (omp_get_thread_num() == 0)
            printf("Worker thread count: %d\n", omp_get_num_threads());

        while (1)
        {
            if (is_end)
                break;

            // Ensure only one thread updates shared buffer at a time
            #pragma omp critical(space)
            {
                if (SIZE - at - 1 > 0) // Ensure there is space left
                {
                    // Produce item and place in warehouse
                    warehouse[++at] = rand();
                    printf("Worker %d produced item %d; at = %d\n", omp_get_thread_num(), warehouse[at], at);
                }
            }

            sleep(SLEEP_WORKERS); // Simulate work delay
        }
    }
}

// Function to simulate consumers consuming items
void start_consumers()
{
    // Set number of OpenMP threads for consumers
    omp_set_num_threads(THREAD_NUM_CONSUMER);

    // Parallel region for consumer threads
    #pragma omp parallel default(shared)
    {
        if (omp_get_thread_num() == 0)
            printf("Consumer thread count: %d\n", omp_get_num_threads());

        while (1)
        {
            if (is_end)
                break;

            // Ensure only one thread removes item at a time
            #pragma omp critical(space)
            {
                if (at >= 0) // Ensure there's something to consume
                {
                    int item = warehouse[at--];
                    printf("Consumer %d consumed item %d; at = %d\n", omp_get_thread_num(), item, at);
                }
            }

            sleep(SLEEP_CONSUMERS); // Simulate work delay
        }
    }
}

int main()
{
    // Disable dynamic team sizes to keep thread count fixed
    omp_set_dynamic(0);

    // Enable nested parallel regions
    omp_set_nested(1);

    // Set 3 threads for 3 tasks: workers, consumers, controller
    omp_set_num_threads(3);

    // Use OpenMP sections to launch 3 concurrent tasks
    #pragma omp parallel sections
    {
        // Section 1: Start worker threads
        #pragma omp section
        {
            start_workers();
        }

        // Section 2: Start consumer threads
        #pragma omp section
        {
            start_consumers();
        }

        // Section 3: Controller (waits for user input to end processing)
        #pragma omp section
        {
            int input;
            printf("Enter 0 to stop:\n");
            scanf("%d", &input);

            if (input == 0)
            {
                // Use critical to safely set the shared flag
                #pragma omp critical(end)
                {
                    is_end = 1;
                }
            }
        }
    }

    return 0;
}

//0 to stop, at is 0(min for worker): position, at is -1(min for consumer):empty
//exemple of producer_workers(15, 2s sleep), consumer(10, 1s sleep), warehouse(memory partage)
//g++ -fopenmp -o openMP_version openMP_version.cpp; ./openMP_version
