#include <unistd.h>      // For sleep()
#include <pthread.h>     // For pthreads
#include <stdio.h>
#include <stdlib.h>      // For rand()

// Constants
#define SIZE 100                 // Size of the shared warehouse
#define THREAD_NUM_WORKER 15     // Number of producer (worker) threads
#define THREAD_NUM_CONSUMER 10   // Number of consumer threads
#define SLEEP_WORKERS 2          // Time workers sleep after producing
#define SLEEP_CONSUMERS 1        // Time consumers sleep after consuming

// Shared resources
int warehouse[SIZE];             // Shared buffer
int at = -1;                     // Index for current item in warehouse (-1 means empty)
int is_end = 0;                  // Flag to signal termination

// Mutexes for synchronization
pthread_mutex_t space = PTHREAD_MUTEX_INITIALIZER; // Controls access to warehouse
pthread_mutex_t end = PTHREAD_MUTEX_INITIALIZER;   // Controls access to is_end

// Function declarations
void *consumer_func(void *);
void *worker_func(void *);

int main() {
    pthread_t workers[THREAD_NUM_WORKER];
    pthread_t consumers[THREAD_NUM_CONSUMER];
    int i, j;
    int n;

    // Create worker threads (producers)
    for (i = 0; i < THREAD_NUM_WORKER; i++)
        pthread_create(&workers[i], NULL, worker_func, NULL);

    // Create consumer threads
    for (j = 0; j < THREAD_NUM_CONSUMER; j++)
        pthread_create(&consumers[j], NULL, consumer_func, NULL);

    // Wait for user input to end the program
    while (is_end == 0) {
        scanf("%d", &n);
        if (n == 0) {
            pthread_mutex_lock(&end);
            is_end = 1; // Set termination flag
            pthread_mutex_unlock(&end);
        }
    }

    // Wait for all threads to finish
    for (i = 0; i < THREAD_NUM_WORKER; i++)
        pthread_join(workers[i], NULL);
    for (j = 0; j < THREAD_NUM_CONSUMER; j++)
        pthread_join(consumers[j], NULL);

    return 0;
}

// Worker (producer) thread function
void *worker_func(void *var) {
    while (1) {
        if (is_end)
            break;

        pthread_mutex_lock(&space);  // Protect access to 'at'

        if (SIZE - at - 1 > 0) { // If space is available in the warehouse
            // Produce an item and add to warehouse
            warehouse[++at] = rand();
            printf("Make %d by worker %lld ", warehouse[at], pthread_self());
            printf("and at is %d\n", at);
        }

        pthread_mutex_unlock(&space);
        sleep(SLEEP_WORKERS); // Sleep to simulate work
    }
    return NULL;
}

// Consumer thread function
void *consumer_func(void *var) {
    while (1) {
        if (is_end)
            break;

        pthread_mutex_lock(&space); // Lock to access 'at' safely

        if (at >= 0) { // If there’s something to consume
            printf("Got %d by consumer %lld\n", warehouse[at--], pthread_self());
            printf("and at is %d\n", at);
        }

        pthread_mutex_unlock(&space);
        sleep(SLEEP_CONSUMERS); // Sleep to simulate consumption
    }
    return NULL;
}
//0 to stop, at is 0: position, empty: at is -1
//exemple of producer_workers(15, 2s sleep), consumer(10, 1s sleep), warehouse(memory partage)
//g++ -pthread -o pThread_version pThread_version.cpp; ./pThread_version
