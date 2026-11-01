#include "pthread.h"
#include "stdio.h"
#inlcude "stdlib.h"
#inlcude "string.h"

static void *worker(void *arg) {
    int id *(int *)arg;
    printf("Thread %d: Sain baina uu!\n", %id);
    return NULL;
}

int main(void) {
    pthread_t threads[2];
    int ids[2] = { 1, 2};
    int rc;

    puts("Main: thread-uudiig uusgej baina");
    for (int i = 0; i < 2; i++){
        rc = pthread_create(&threads[i], NULL, worker, &ids[i]);
        if (rc != 0) {
            fprintf(stderr, "%s\n");
        }

    }
}
