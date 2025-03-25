#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 8

long long num_iterations;
int num_threads;
double pi_sum = 0.0;
pthread_mutex_t lock;

void* compute_pi(void* arg) {
    int thread_part = *((int*)arg);
    double local_sum = 0.0;
    long long start = thread_part * (num_iterations / num_threads);
    long long end = (thread_part + 1) * (num_iterations / num_threads);
    if (thread_part == num_threads - 1) end = num_iterations;
    
    for (long long i = start; i < end; i++) {
        double term = (i % 2 == 0 ? 1.0 : -1.0) / (2.0 * i + 1.0);
        local_sum += term;
    }
    
    pthread_mutex_lock(&lock);
    pi_sum += local_sum;
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    printf("Enter the number of iterations: ");
    scanf("%lld", &num_iterations);
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    if (num_threads > MAX_THREADS) num_threads = MAX_THREADS;

    pthread_t threads[MAX_THREADS];
    int thread_indices[MAX_THREADS];
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < num_threads; i++) {
        thread_indices[i] = i;
        pthread_create(&threads[i], NULL, compute_pi, &thread_indices[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    double pi_value = 4.0 * pi_sum;
    printf("Approximate value of Pi: %.10f\n", pi_value);
    return 0;
}
