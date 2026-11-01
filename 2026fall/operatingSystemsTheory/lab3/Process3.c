#include <stdio.h>
#include <string.h>
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

int main(void)
{
    struct PCB pcb = {3, 1, READY, 0};
    char text[] = "operating system";
    int count[256];
    int i;

    while (1) {
        pcb.state = RUNNING;
        pcb.process_counter++;

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
        print_pcb(pcb);

        pcb.state = WAITING;
        sleep(1);
    }

    return 0;
}
