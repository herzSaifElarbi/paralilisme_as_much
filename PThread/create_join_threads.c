#include <stdio.h>
#include <pthread.h>

void *print_message(void *msg) {
    printf("%s\n", (char *)msg);
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;
    char *msg1 = "Hello from Thread 1";
    char *msg2 = "Hello from Thread 2";

    // Create threads
    pthread_create(&t1, NULL, print_message, (void *)msg1);
    pthread_create(&t2, NULL, print_message, (void *)msg2);

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}