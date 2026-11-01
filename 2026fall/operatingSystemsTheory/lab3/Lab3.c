#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void print_array(int a[], int n)
{
    int i;

    for (i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void sort_array(int a[], int n)
{
    int i, j, temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

void process1_step(struct PCB *pcb)
{
    int numbers[10];
    int n = 10;
    int i;

    pcb->state = RUNNING;
    pcb->process_counter++;

    printf("\n--- Process 1: Random array sort ---\n");
    for (i = 0; i < n; i++) {
        numbers[i] = rand() % 100;
    }

    printf("Random array: ");
    print_array(numbers, n);
    sort_array(numbers, n);
    printf("Sorted array: ");
    print_array(numbers, n);
    print_pcb(*pcb);

    pcb->state = READY;
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

void process2_step(struct PCB *pcb)
{
    int a[3][3], b[3][3], c[3][3];
    int m = 3, n = 3;
    int i, j;

    pcb->state = RUNNING;
    pcb->process_counter++;

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
    print_pcb(*pcb);

    pcb->state = READY;
}

void process3_step(struct PCB *pcb)
{
    char text[] = "operating system";
    int count[256];
    int i;

    pcb->state = RUNNING;
    pcb->process_counter++;

    for (i = 0; i < 256; i++) {
        count[i] = 0;
    }

    for (i = 0; text[i] != '\0'; i++) {
        count[(unsigned char)text[i]]++;
    }

    printf("\n--- Process 3: Character frequency ---\n");
    printf("String: \"%s\"\n", text);
    printf("Frequency:\n");
    for (i = 0; i < 256; i++) {
        if (count[i] > 0) {
            if (i == ' ') {
                printf("'space': %d\n", count[i]);
            } else {
                printf("'%c': %d\n", i, count[i]);
            }
        }
    }
    print_pcb(*pcb);

    pcb->state = READY;
}

int main(void)
{
    struct PCB p1 = {1, 3, READY, 0};
    struct PCB p2 = {2, 2, READY, 0};
    struct PCB p3 = {3, 1, READY, 0};

    srand(time(NULL));

    printf("Lab 3 - PCB ба round-robin simulation\n");
    printf("Програмыг зогсоох бол CTRL + C дарна.\n");

    while (1) {
        process1_step(&p1);
        process2_step(&p2);
        process3_step(&p3);

        printf("\nНэг round дууслаа.\n");
        sleep(1);
    }

    return 0;
}
