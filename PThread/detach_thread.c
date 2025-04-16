#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *detached_worker(void *arg) {
    printf("Detached thread running\n");
    sleep(2);
    printf("Detached thread exiting\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t t;
    pthread_create(&t, NULL, detached_worker, NULL);
    pthread_detach(t); // Detach the thread
    printf("Main thread exiting\n");
    return 0;
}