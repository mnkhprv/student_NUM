#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NEW 0
#define READY 1
#define RUNNING 2
#define WAITING 3
#define TERMINATED 4

#define PROCESS_COUNT 3

struct PCB {
    int process_id;
    int priority;
    int state;
    int process_counter;
    int burst_time;
    int waiting_time;
};

const char *getStateName(int state) {
    switch (state) {
        case NEW:
            return "NEW";
        case READY:
            return "READY";
        case RUNNING:
            return "RUNNING";
        case WAITING:
            return "WAITING";
        case TERMINATED:
            return "TERMINATED";
        default:
            return "UNKNOWN";
    }
}

void printPCB(struct PCB p) {
    printf("PID: %d | Priority: %d | State: %-10s | Counter: %d | Burst: %d | Waiting: %d\n",
           p.process_id, p.priority, getStateName(p.state),
           p.process_counter, p.burst_time, p.waiting_time);
}

void printAllProcesses(struct PCB processes[], int n) {
    int i;

    printf("\nProcess table:\n");
    for (i = 0; i < n; i++) {
        printPCB(processes[i]);
    }
    printf("\n");
}

void contextSwitch(struct PCB *current, struct PCB *next) {
    if (current == NULL) {
        printf("[Context Switch] CPU -> Process %d\n", next->process_id);
    } else if (current->process_id != next->process_id) {
        printf("[Context Switch] Process %d -> Process %d\n",
               current->process_id, next->process_id);
    }

    printf("Loading state of Process %d...\n", next->process_id);
}

int selectNextProcess(struct PCB processes[], int n) {
    int i;
    int selected = -1;

    /* Priority бага байх тусам илүү өндөр эрхтэй гэж үзэв. */
    for (i = 0; i < n; i++) {
        if (processes[i].state == READY) {
            if (selected == -1 || processes[i].priority < processes[selected].priority) {
                selected = i;
            }
        }
    }

    return selected;
}

void updateWaitingProcesses(struct PCB processes[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        if (processes[i].state == WAITING) {
            processes[i].waiting_time--;
            printf("Process %d is WAITING. Remaining wait = %d\n",
                   processes[i].process_id, processes[i].waiting_time);

            if (processes[i].waiting_time <= 0) {
                processes[i].state = READY;
                printf("Process %d state changed to READY\n", processes[i].process_id);
            }
        }
    }
}

void finishOrReady(struct PCB *p) {
    if (p->burst_time <= 0) {
        p->state = TERMINATED;
        printf("Process %d finished. State changed to TERMINATED\n", p->process_id);
    } else {
        p->state = READY;
        printf("Process %d state changed to READY\n", p->process_id);
    }
}

void process1(struct PCB *p) {
    int numbers[5];
    int i, j, temp;

    printf("Process 1 is RUNNING: random numbers sorting\n");

    for (i = 0; i < 5; i++) {
        numbers[i] = rand() % 100;
    }

    for (i = 0; i < 4; i++) {
        for (j = i + 1; j < 5; j++) {
            if (numbers[i] > numbers[j]) {
                temp = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = temp;
            }
        }
    }

    printf("Sorted numbers: ");
    for (i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    p->process_counter++;
    p->burst_time--;
    finishOrReady(p);
}

void process2(struct PCB *p) {
    int a[2][2] = {{1, 2}, {3, 4}};
    int b[2][2] = {{5, 6}, {7, 8}};
    int c[2][2];
    int i, j;

    printf("Process 2 is RUNNING: matrix addition\n");

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }

    printf("Matrix result: [[%d, %d], [%d, %d]]\n",
           c[0][0], c[0][1], c[1][0], c[1][1]);

    p->process_counter++;
    p->burst_time--;

    if (p->burst_time > 0 && p->process_counter == 1) {
        p->state = WAITING;
        p->waiting_time = 2;
        printf("Process 2 needs I/O. State changed to WAITING\n");
    } else {
        finishOrReady(p);
    }
}

void process3(struct PCB *p) {
    char text[] = "operating system";
    int freq[26] = {0};
    int i;

    printf("Process 3 is RUNNING: character frequency count\n");

    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            freq[text[i] - 'a']++;
        }
    }

    printf("Frequency: ");
    for (i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            printf("%c=%d ", 'a' + i, freq[i]);
        }
    }
    printf("\n");

    p->process_counter++;
    p->burst_time--;
    finishOrReady(p);
}

int allTerminated(struct PCB processes[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        if (processes[i].state != TERMINATED) {
            return 0;
        }
    }

    return 1;
}

void runProcess(struct PCB *p) {
    if (p->process_id == 1) {
        process1(p);
    } else if (p->process_id == 2) {
        process2(p);
    } else if (p->process_id == 3) {
        process3(p);
    }
}

int main(void) {
    struct PCB processes[PROCESS_COUNT] = {
        {1, 1, READY, 0, 3, 0},
        {2, 2, READY, 0, 3, 0},
        {3, 3, READY, 0, 3, 0}
    };
    struct PCB *current = NULL;
    int selected;
    int time_step = 1;
    srand(time(NULL));
    printf("Lab 4: Process State, Priority and Context Switching Simulation\n");
    printf("Priority rule: smaller number means higher priority.\n");
    printAllProcesses(processes, PROCESS_COUNT);
    while (!allTerminated(processes, PROCESS_COUNT)) {
        printf("----------------------------------\n");
        printf("Time step %d\n", time_step);

        updateWaitingProcesses(processes, PROCESS_COUNT);
        selected = selectNextProcess(processes, PROCESS_COUNT);
        if (selected == -1) {
            printf("No READY process. CPU is idle.\n");
            time_step++;
            continue;
        }
        printf("CPU Scheduler selected Process %d\n", processes[selected].process_id);
        contextSwitch(current, &processes[selected]);
        processes[selected].state = RUNNING;
        runProcess(&processes[selected]);
        current = &processes[selected];

        printAllProcesses(processes, PROCESS_COUNT);
        time_step++;
    }

    printf("All processes are TERMINATED.\n");

    return 0;
}
