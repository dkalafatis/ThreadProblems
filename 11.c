#include <stdio.h>
#include <pthread.h>

int result; // Shared variable for the result
int result_ready = 0; // Flag indicating if result is ready

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *calculate(void *arg) {
    int sum = 0;
    // Perform an arithmetic calculation: sum of numbers from 1 to 100
    for (int i = 1; i <= 100; i++) {
        sum += i;
    }

    // Lock mutex before updating shared variables
    pthread_mutex_lock(&mutex);
    result = sum;
    result_ready = 1; // Indicate that the result is ready
    pthread_cond_signal(&cond); // Signal the waiting thread
    pthread_mutex_unlock(&mutex); // Unlock mutex

    return NULL;
}

void *display(void *arg) {
    // Lock mutex before checking shared variables
    pthread_mutex_lock(&mutex);
    while (!result_ready) {
        // Wait for the signal that the result is ready
        pthread_cond_wait(&cond, &mutex);
    }
    printf("The result is: %d\n", result);
    pthread_mutex_unlock(&mutex); // Unlock mutex

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Create the calculation and display threads
    pthread_create(&thread1, NULL, calculate, NULL);
    pthread_create(&thread2, NULL, display, NULL);

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
