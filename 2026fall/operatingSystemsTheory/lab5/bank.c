#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int balance = 1000;
static int rejected = 0;
static pthread_mutex_t lock;

static void check(int rc, const char *what) {
    if (rc != 0) {
        fprintf(stderr, "%s: %s\n", what, strerror(rc));
        exit(EXIT_FAILURE);
    }
}

/* 50 negjiig count udaa nemne */
static void *deposit(void *arg) {
    int count = *(int *)arg;
    for (int i = 0; i < count; i++) {
        check(pthread_mutex_lock(&lock), "mutex_lock");
        balance += 50;
        check(pthread_mutex_unlock(&lock), "mutex_unlock");
    }
    return NULL;
}

/* 30 negjiig count udaa hasna, uldegdel hureltsehgui bol tatgalzana */
static void *withdraw(void *arg) {
    int count = *(int *)arg;
    for (int i = 0; i < count; i++) {
        check(pthread_mutex_lock(&lock), "mutex_lock");
        if (balance >= 30)
            balance -= 30;
        else
            rejected++;
        check(pthread_mutex_unlock(&lock), "mutex_unlock");
    }
    return NULL;
}

/* ./bank      -> undsen test (A, C)
   ./bank b    -> test B: balance=20, deposit baihgui, withdraw 1 udaa */
int main(int argc, char *argv[]) {
    pthread_t t1, t2;
    int deposit_count = 10, withdraw_count = 10;

    if (argc > 1 && strcmp(argv[1], "b") == 0) {
        balance = 20;
        deposit_count = 0;
        withdraw_count = 1;
    } else if (argc > 1) {
        fprintf(stderr, "Hereglee: %s [b]\n", argv[0]);
        return EXIT_FAILURE;
    }

    check(pthread_mutex_init(&lock, NULL), "mutex_init");
    check(pthread_create(&t1, NULL, deposit, &deposit_count), "create deposit");
    check(pthread_create(&t2, NULL, withdraw, &withdraw_count), "create withdraw");
    check(pthread_join(t1, NULL), "join deposit");
    check(pthread_join(t2, NULL), "join withdraw");

    printf("Final balance: %d\n", balance);
    printf("Rejected withdrawals: %d\n", rejected);

    check(pthread_mutex_destroy(&lock), "mutex_destroy");
    return EXIT_SUCCESS;
}
