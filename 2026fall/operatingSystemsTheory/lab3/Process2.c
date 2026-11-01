#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define READY 0
#define RUNNING 1
#define WAITING 2

struct PCB {
    int process_id;
    int priority;
    int state;
    int process_counter;
};

void print_pcb(struct PCB pcb)
{
    printf("PCB: PID=%d, Priority=%d, State=%d, Counter=%d\n",
           pcb.process_id, pcb.priority, pcb.state, pcb.process_counter);
}

void print_matrix(int matrix[3][3], int m, int n)
{
    int i, j;

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    struct PCB pcb = {2, 2, READY, 0};
    int m = 3, n = 3;
    int a[3][3], b[3][3], c[3][3];
    int i, j;

    srand(time(NULL));

    while (1) {
        pcb.state = RUNNING;
        pcb.process_counter++;

        printf("\n--- Process 2: Matrix addition ---\n");
        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) {
                a[i][j] = rand() % 10;
                b[i][j] = rand() % 10;
                c[i][j] = a[i][j] + b[i][j];
            }
        }

        printf("A matrix:\n");
        print_matrix(a, m, n);
        printf("B matrix:\n");
        print_matrix(b, m, n);
        printf("C = A + B:\n");
        print_matrix(c, m, n);
        print_pcb(pcb);

        pcb.state = WAITING;
        sleep(1);
    }

    return 0;
}
