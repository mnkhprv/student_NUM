#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock1;
pthread_mutex_t lock2;

/* Хоёр thread хоёулаа lock1 -> lock2 дарааллаар авна */
void* safe_thread_func(void* arg) {
    char* name = arg;

    printf("%s: lock1 авах гэж байна...\n", name);
    pthread_mutex_lock(&lock1);
    printf("%s: lock1 авлаа\n", name);

    sleep(1);

    printf("%s: lock2 авах гэж байна...\n", name);
    pthread_mutex_lock(&lock2);
    printf("%s: lock2 авлаа\n", name);

    printf("%s: critical section-д ажиллаж байна...\n", name);

    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);

    printf("%s: ажил дууслаа\n", name);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    pthread_create(&t1, NULL, safe_thread_func, "Thread 1");
    pthread_create(&t2, NULL, safe_thread_func, "Thread 2");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);

    printf("Main: deadlock үүсгэлгүй програм дууслаа\n");
    return 0;
}
