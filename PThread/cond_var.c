#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int condition_met = 0;

void *waiter(void *arg) {
    pthread_mutex_lock(&mutex);
    while (!condition_met) {
        pthread_cond_wait(&cond, &mutex); // Wait for signal
    }
    printf("Condition met!\n");
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void *signaler(void *arg) {
    sleep(2); // Simulate work
    pthread_mutex_lock(&mutex);
    condition_met = 1;
    pthread_cond_signal(&cond); // Notify waiter
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, waiter, NULL);
    pthread_create(&t2, NULL, signaler, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}