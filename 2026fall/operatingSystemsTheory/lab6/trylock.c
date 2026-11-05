#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock1;
pthread_mutex_t lock2;

/*
 * Өргөтгөл: lock-ийн дараалал анхны кодтой адил эсрэг хэвээр.
 * Харин 2 дахь lock-ийг pthread_mutex_trylock-оор авна.
 * Авч чадахгүй бол эхний lock-оо суллаад, хэсэг хүлээгээд дахин оролдоно.
 */
void* thread1_func(void* arg) {
    int tries = 0;

    while (1) {
        tries++;
        pthread_mutex_lock(&lock1);
        printf("Thread 1: lock1 авлаа (оролдлого %d)\n", tries);
        sleep(1);

        if (pthread_mutex_trylock(&lock2) == 0) {
            printf("Thread 1: lock2 авлаа\n");
            break;
        }
        printf("Thread 1: lock2 завгүй, lock1-ийг сулласан\n");
        pthread_mutex_unlock(&lock1);
        usleep(200000);   /* 0.2 секунд */
    }

    printf("Thread 1: critical section-д ажиллаж байна...\n");
    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);
    printf("Thread 1: ажил дууслаа (%d оролдлого)\n", tries);
    return NULL;
}

void* thread2_func(void* arg) {
    int tries = 0;

    while (1) {
        tries++;
        pthread_mutex_lock(&lock2);
        printf("Thread 2: lock2 авлаа (оролдлого %d)\n", tries);
        sleep(1);

        if (pthread_mutex_trylock(&lock1) == 0) {
            printf("Thread 2: lock1 авлаа\n");
            break;
        }
        printf("Thread 2: lock1 завгүй, lock2-ийг сулласан\n");
        pthread_mutex_unlock(&lock2);
        usleep(700000);   /* өөр хугацаа хүлээнэ, эс тэгвэл livelock болж болно */
    }

    printf("Thread 2: critical section-д ажиллаж байна...\n");
    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);
    printf("Thread 2: ажил дууслаа (%d оролдлого)\n", tries);
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

    printf("Main: trylock ашиглаж deadlock-оос гарлаа\n");
    return 0;
}
