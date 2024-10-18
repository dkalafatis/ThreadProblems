#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int max_value;
int min_value;

void* thread_max(void* arg) {
    int* nums = (int*)arg;
    int num1 = nums[0];
    int num2 = nums[1];
    if (num1 > num2)
        max_value = num1;
    else
        max_value = num2;
    pthread_exit(NULL);
}

void* thread_min(void* arg) {
    int* nums = (int*)arg;
    int num1 = nums[0];
    int num2 = nums[1];
    if (num1 < num2)
        min_value = num1;
    else
        min_value = num2;
    pthread_exit(NULL);
}

void* thread_avg(void* arg) {
    int* nums = (int*)arg;
    int num1 = nums[0];
    int num2 = nums[1];
    double avg = (num1 + num2) / 2.0;
    printf("Average: %.2f\n", avg);
    pthread_exit(NULL);
}

int main() {
    int num1, num2;
    pthread_t tid_max, tid_min, tid_avg;
    int nums[2];

    // Get input from user
    printf("Enter two integers:\n");
    scanf("%d%d", &num1, &num2);

    nums[0] = num1;
    nums[1] = num2;

    // Create thread_max
    pthread_create(&tid_max, NULL, thread_max, nums);

    // Create thread_min
    pthread_create(&tid_min, NULL, thread_min, nums);

    // Wait for thread_max and thread_min to finish
    pthread_join(tid_max, NULL);
    pthread_join(tid_min, NULL);

    // Display the largest and smallest numbers
    printf("Largest number: %d\n", max_value);
    printf("Smallest number: %d\n", min_value);

    // Create average thread
    pthread_create(&tid_avg, NULL, thread_avg, nums);

    // Wait for the average thread to finish
    pthread_join(tid_avg, NULL);

    return 0;
}
