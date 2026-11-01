#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOOPS 500000
static long counter = 0;
static pthread_mutex_t lock;

static void check(int rc, const char *what) {
    if (rc != 0) {
        fprintf(stderr, "%s: %s\n", what, strerror(rc));
        exit(EXIT_FAILURE);
    }
}

static void *increase(void *arg) {
    (void)arg;
    for (long i = 0; i < LOOPS; i++) {
        check(pthread_mutex_lock(&lock), "mutex_lock");
        counter++;
        check(pthread_mutex_unlock(&lock), "mutex_unlock");
    }
    return NULL;
}

int main(void) {
    pthread_t t[2];
    check(pthread_mutex_init(&lock, NULL), "mutex_init");
    for (int i = 0; i < 2; i++)
        check(pthread_create(&t[i], NULL, increase, NULL), "create");
    for (int i = 0; i < 2; i++)
        check(pthread_join(t[i], NULL), "join");
    printf("Expected: %ld, observed: %ld\n", 2L * LOOPS, counter);
    check(pthread_mutex_destroy(&lock), "mutex_destroy");
    return EXIT_SUCCESS;
}
