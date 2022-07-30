#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

struct PROCESS{
    int order;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

void SortingArrivalTime(struct PROCESS* process, int process_count){
    for (int i = 1; i < process_count; ++i) {
        for (int j = 0; j < process_count - i; ++j) {
            if(process[j].arrival_time > process[j + 1].arrival_time){
                struct PROCESS temp = process[j];
                process[j] = process[j + 1];
                process[j+1] = temp;
            }
        }
    }
}

void FCFS_WaitingTime(struct PROCESS* process, int process_count){
    int accumulated_waiting_time = 0;
    for (int i = 0; i < process_count; ++i) {
        process[i].waiting_time = accumulated_waiting_time - process[i].arrival_time;
        accumulated_waiting_time += process[i].burst_time;
    }
}

void FCFS_TurnaroundTime(struct PROCESS* process, int process_count){
    for (int i = 0; i < process_count; ++i) {
        process[i].turnaround_time = process[i].waiting_time + process[i].burst_time;
    }
}

void FCFS_ExecutionOrder(struct PROCESS* process, int process_count){
    printf("Execution Order\n");
    for (int i = 0; i < process_count; ++i) {
        printf("P%d",process[i].order);
    }
    printf("\n");
}


void RR_WaitingTime(struct PROCESS* process, int process_count){
    for (int i = 0; i < process_count; ++i) {
        process[i].waiting_time = process[i].turnaround_time - process[i].burst_time;

    }
}

void RR_TurnaroundTime(struct PROCESS* process, int process_count, int time_quantum){
    int accumulated_time = 0;
    int burst_time[process_count];
    for (int i = 0; i < process_count; ++i) {
        burst_time[i] = process[i].burst_time;
    }
    int flag = true;
    while(flag){
        flag = false;
        for (int i = 0; i < process_count; ++i) {
            if(burst_time[i] != 0){
                flag = true;
                break;
            }
        }
        for (int i = 0; i < process_count; ++i) {
            if(burst_time[i] > time_quantum){
                accumulated_time += time_quantum;
                burst_time[i] -= time_quantum;
            }
            else if(burst_time[i] == 0){
                continue;
            }
            else{
                accumulated_time += burst_time[i];
                burst_time[i] = 0;
                process[i].turnaround_time = accumulated_time - process[i].arrival_time;
            }
        }
    }
}

void RR_ExecutionOrder(struct PROCESS* process, int process_count, int time_quantum){
    printf("Execution Order\n");
    int burst_time[process_count];
    for (int i = 0; i < process_count; ++i) {
        burst_time[i] = process[i].burst_time;
    }
    int flag = true;
    while(flag){
        flag = false;
        for (int i = 0; i < process_count; ++i) {
            if(burst_time[i] != 0){
                flag = true;
                break;
            }
        }
        for (int i = 0; i < process_count; ++i) {
            if(burst_time[i] >= time_quantum){
                printf("P%d", process[i].order);
                burst_time[i] -= time_quantum;
            }
            else if(burst_time[i] == 0){
                continue;
            }
            else{
                printf("P%d", process[i].order);
                burst_time[i] = 0;
            }
        }
    }

    printf("\n");
}

float AverageWaitingTime(struct PROCESS* process, int process_count){
    float average = 0;
    int sum = 0;
    for (int i = 0; i < process_count; ++i) {
        sum += process[i].waiting_time;
    }
    average = (float)sum / (float)process_count;
    return average;
}

float AverageTurnaroundTime(struct PROCESS* process, int process_count){
    float average = 0;
    int sum = 0;
    for (int i = 0; i < process_count; ++i) {
        sum += process[i].turnaround_time;
    }
    average = (float)sum / (float)process_count;
    return average;
}


int main() {
    int process_count = 0;
    printf("Input number of process:\n");
    scanf("%d", &process_count);
    struct PROCESS* FCFS_process = malloc(sizeof(struct PROCESS) * process_count);
    struct PROCESS* RR_process = malloc(sizeof(struct PROCESS) * process_count);
    printf("Input process's arrival time and burst time");
    for (int i = 0; i < process_count; ++i) {
        FCFS_process[i].order = i+1;
        FCFS_process[i].waiting_time = 0;
        FCFS_process[i].turnaround_time = 0;
        scanf("%d %d", &FCFS_process[i].arrival_time, &FCFS_process[i].burst_time);
    }
    for (int i = 0; i < process_count; ++i) {
        RR_process[i] = FCFS_process[i];
    }
    printf("Input time quantum\n");

    int time_quantum = 0;
    scanf("%d", &time_quantum);

    printf("FCFS scheduler\n");
    SortingArrivalTime(FCFS_process, process_count);
    FCFS_WaitingTime(FCFS_process, process_count);
    FCFS_TurnaroundTime(FCFS_process, process_count);
    FCFS_ExecutionOrder(FCFS_process, process_count);

    for (int i = 0; i < process_count; ++i) {
        printf("P%d -> Arrival time: %d, Burst time: %d, Waiting time: %d, Turnaround time: %d\n",
               FCFS_process[i].order, FCFS_process[i].arrival_time, FCFS_process[i].burst_time, FCFS_process[i].waiting_time, FCFS_process[i].turnaround_time);
    }
    printf("Average Waiting time : %.3f\n", AverageWaitingTime(FCFS_process, process_count));
    printf("Average Turnaround time : %.3f\n", AverageTurnaroundTime(FCFS_process, process_count));

    printf("\n\nRR scheduler\n");
    SortingArrivalTime(RR_process, process_count);

    RR_ExecutionOrder(RR_process, process_count, time_quantum);
    RR_TurnaroundTime(RR_process, process_count, time_quantum);
    RR_WaitingTime(RR_process, process_count);

    for (int i = 0; i < process_count; ++i) {
        printf("P%d -> Arrival time: %d, Burst time: %d, Waiting time: %d, Turnaround time: %d\n",
               RR_process[i].order, RR_process[i].arrival_time, RR_process[i].burst_time, RR_process[i].waiting_time, RR_process[i].turnaround_time);
    }
    printf("\nAverage Waiting time : %.3f\n", AverageWaitingTime(RR_process, process_count));
    printf("Average Turnaround time : %.3f\n", AverageTurnaroundTime(RR_process, process_count));
    free(FCFS_process);
    free(RR_process);
}





















