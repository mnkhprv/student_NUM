#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock1;
pthread_mutex_t lock2;

void* thread1_func(void* arg) {
    printf("Thread 1: lock1 авах гэж байна...\n");
    pthread_mutex_lock(&lock1);
    printf("Thread 1: lock1 авлаа\n");

    sleep(1);

    printf("Thread 1: lock2 авах гэж байна...\n");
    pthread_mutex_lock(&lock2);
    printf("Thread 1: lock2 авлаа\n");

    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);
    printf("Thread 1: ажил дууслаа\n");
    return NULL;
}

void* thread2_func(void* arg) {
    printf("Thread 2: lock2 авах гэж байна...\n");
    pthread_mutex_lock(&lock2);
    printf("Thread 2: lock2 авлаа\n");

    sleep(1);

    printf("Thread 2: lock1 авах гэж байна...\n");
    pthread_mutex_lock(&lock1);
    printf("Thread 2: lock1 авлаа\n");

    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);
    printf("Thread 2: ажил дууслаа\n");
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    pthread_create(&t1, NULL, thread1_func, NULL);
    pthread_create(&t2, NULL, thread2_func, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);

    printf("Main: програм дууслаа\n");
    return 0;
}
