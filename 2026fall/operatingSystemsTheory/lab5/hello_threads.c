#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 3

static void *worker(void *arg) {
    int id = *(int *)arg;
    printf("Thread %d: Sain baina uu!\n", id);
    return NULL;
}

int main(void) {
    pthread_t threads[N];
    int ids[N] = {1, 2, 3};
    int rc;

    puts("Main: thread-uudiig uusgej baina.");
    for (int i = 0; i < N; i++) {
        rc = pthread_create(&threads[i], NULL, worker, &ids[i]);
        if (rc != 0) {
            fprintf(stderr, "pthread_create: %s\n", strerror(rc));
            for (int j = 0; j < i; j++) pthread_join(threads[j], NULL);
            return EXIT_FAILURE;
        }
    }
    for (int i = 0; i < N; i++) {
        rc = pthread_join(threads[i], NULL);
        if (rc != 0) {
            fprintf(stderr, "pthread_join: %s\n", strerror(rc));
            return EXIT_FAILURE;
        }
    }
    puts("Main: buh thread duussan.");
    return EXIT_SUCCESS;
}
