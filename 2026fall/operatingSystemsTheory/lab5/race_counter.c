#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Тоог -DTHREADS=3 -DLOOPS=100000 гэж compile хийхдээ өөрчилж болно */
#ifndef THREADS
#define THREADS 2
#endif
#ifndef LOOPS
#define LOOPS 500000
#endif

static long counter = 0;

static void *increase(void *arg) {
    (void)arg;
    for (long i = 0; i < LOOPS; i++) {
        counter++; /* zoriud synchronization hiigeegui */
    }
    return NULL;
}

int main(void) {
    pthread_t t[THREADS];
    for (int i = 0; i < THREADS; i++) {
        int rc = pthread_create(&t[i], NULL, increase, NULL);
        if (rc != 0) {
            fprintf(stderr, "pthread_create: %s\n", strerror(rc));
            for (int j = 0; j < i; j++) pthread_join(t[j], NULL);
            return EXIT_FAILURE;
        }
    }
    for (int i = 0; i < THREADS; i++) {
        int rc = pthread_join(t[i], NULL);
        if (rc != 0) {
            fprintf(stderr, "pthread_join: %s\n", strerror(rc));
            return EXIT_FAILURE;
        }
    }
    printf("Expected: %ld, observed: %ld\n", (long)THREADS * LOOPS, counter);
    return EXIT_SUCCESS;
}
