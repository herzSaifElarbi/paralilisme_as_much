#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void cleanup(void *arg) {
    printf("Cleanup: %s\n", (char *)arg);
}

void *worker(void *arg) {
    pthread_cleanup_push(cleanup, "Resource freed");
    while (1) {
        sleep(1);
        printf("Working...\n");
        pthread_testcancel(); // Check for cancellation
    }
    pthread_cleanup_pop(0);
    pthread_exit(NULL);
}

int main() {
    pthread_t t;
    pthread_create(&t, NULL, worker, NULL);
    sleep(3); // Let the thread run for 3 seconds
    pthread_cancel(t); // Cancel the thread
    pthread_join(t, NULL);
    return 0;
}