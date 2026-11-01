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

int main(void)
{
    struct PCB pcb = {1, 3, READY, 0};
    int n = 10;
    int numbers[10];
    int i;

    srand(time(NULL));

    while (1) {
        pcb.state = RUNNING;
        pcb.process_counter++;

        printf("\n--- Process 1: Random array sort ---\n");
        for (i = 0; i < n; i++) {
            numbers[i] = rand() % 100;
        }

        printf("Random array: ");
        print_array(numbers, n);

        sort_array(numbers, n);

        printf("Sorted array: ");
        print_array(numbers, n);
        print_pcb(pcb);

        pcb.state = WAITING;
        sleep(1);
    }

    return 0;
}
