
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Dqueue_int.h"
struct process
{
    int burst_time;
    int arrival_time;
    int priority;
    int waiting_time;
    int Ct;
    int remaining_time;
    int Tat;
    int inqueue;
};

void fcfs(struct process *processes, int num_processes)
{
    // Initialize the waiting times.
    int waiting_times[num_processes];
    for (int i = 0; i < num_processes; i++)
    {
        processes[i].waiting_time = 0;
        processes[i].Tat = 0;
        processes[i].Ct = 0;
    }
    char gantt[30][10];
    int ganttptr=0;
    char gantt2[30][10];
    int ganttptr2=0;

    // Calculate the waiting times.
    int min = 0;
    int prevmin = -1;
    int timeline = 0;
    for (int i = 0; i < num_processes; i++)
    {
        for (int j = 0; j < num_processes; j++)
        {
            if (processes[min].Ct != 0)
            {
                for (int x = 0; x < num_processes; x++)
                {
                    if (processes[j].Ct == 0)
                    {
                        min = j;
                        break;
                    }
                }
            }

            if (processes[min].arrival_time >= processes[j].arrival_time && processes[j].Ct == 0 && processes[j].arrival_time <= timeline)
            {
                prevmin = min;
                min = j;
            }
        }
        // printf("\n Process %d %d %d", min, prevmin, processes[min].Ct);
        sprintf(gantt[ganttptr],"P%d",min);
        sprintf(gantt2[ganttptr2],"%d",timeline);
        ganttptr++;
        ganttptr2++;
        timeline += processes[min].burst_time;
        processes[min].Ct = timeline;
        processes[min].Tat = processes[min].Ct - processes[min].arrival_time;
        processes[min].waiting_time = processes[min].Tat - processes[min].burst_time;
    }

    // Calculate the turnaround times.
    double avgtat = 0, avgwt = 0;
    for (int i = 0; i < num_processes; i++)
    {
        avgtat += processes[i].Tat;
        avgwt += processes[i].waiting_time;
    }
    avgtat = avgtat / num_processes;
    avgwt = avgwt / num_processes;
    printf("Gantt chart:\n");
    for(int x=0;x<ganttptr;x++){
        printf("| %s |",gantt[x]);
        if(x+1 != ganttptr){
            printf(" ---- ");
        }
    }
    printf("\n");
     for(int x=0;x<ganttptr2;x++){
        printf("  %s  ",gantt2[x]);
        if(x+1 != ganttptr2){
            printf(" ---- ");
        }
    }
     printf("\n");
    printf("Average waiting time: %f\n", avgwt);
    printf("Average turnaround time: %f\n", avgtat);
}

void SJF_NP(struct process *processes, int num_processes)
{
    // Initialize the waiting times.
    int waiting_times[num_processes];
    for (int i = 0; i < num_processes; i++)
    {
        processes[i].waiting_time = 0;
        processes[i].Tat = 0;
        processes[i].Ct = 0;
    }
    

    // Calculate the waiting times.
    int min = 0;
    int timeline = 0;
    for (int i = 0; i < num_processes; i++)
    {
        for (int j = 0; j < num_processes; j++)
        {
            if (processes[min].Ct != 0)
            {
            Start:
                int temp = min;
                for (int x = 0; x < num_processes; x++)
                {
                    if (processes[x].Ct == 0 && processes[x].arrival_time <= timeline)
                    {
                        min = x;
                        break;
                    }
                }
                if (min == temp && min != 0)
                {
                    timeline++;
                    goto Start;
                }
            }

            if (processes[min].burst_time >= processes[j].burst_time && processes[j].Ct == 0 && processes[j].arrival_time <= timeline)
            {
                min = j;
            }
        }
       // printf("\n Process %d  %d %d", timeline, min, processes[min].burst_time);
        timeline += processes[min].burst_time;
        processes[min].Ct = timeline;
        processes[min].Tat = processes[min].Ct - processes[min].arrival_time;
        processes[min].waiting_time = processes[min].Tat - processes[min].burst_time;
    }

    // Calculate the turnaround times.
    double avgtat = 0, avgwt = 0;
    for (int i = 0; i < num_processes; i++)
    {
        avgtat += processes[i].Tat;
        avgwt += processes[i].waiting_time;
    }
    avgtat = avgtat / num_processes;
    avgwt = avgwt / num_processes;
    printf("Average waiting time: %f\n", avgwt);
    printf("Average turnaround time: %f\n", avgtat);
}

void SJF_P(struct process *processes, int num_processes)
{
    // Initialize the waiting times.
    int waiting_times[num_processes];
    int Totalbt = 0;
    for (int i = 0; i < num_processes; i++)
    {
        processes[i].waiting_time = 0;
        processes[i].Tat = 0;
        processes[i].Ct = 0;
        processes[i].remaining_time = processes[i].burst_time;
        Totalbt += processes[i].burst_time;
    }
    // Calculate the waiting times.
    int min = 0;
    int timeline = 0;
    bool found = false;
    int processcompletioncount = 0;
    while (timeline < Totalbt)

    {
        found = false;
        for (int j = 0; j < num_processes; j++)
        {
            if (processes[j].arrival_time <= timeline && processes[j].Ct == 0)
            {
                found = true;
                for (int x = 0; x < num_processes; x++)
                {
                    if (processes[j].Ct == 0)
                    {
                        min = j;
                        break;
                    }
                }
                if (processes[min].remaining_time > processes[j].remaining_time && processes[j].Ct == 0)
                {
                    min = j;
                }
            }
        }
        if (found)
        {
            timeline += 1;
            if (processes[min].remaining_time == 1)
            {
                processes[min].remaining_time -= 1;
                processes[min].Ct = timeline;
                processes[min].Tat = processes[min].Ct - processes[min].arrival_time;
                processes[min].waiting_time = processes[min].Tat - processes[min].burst_time;
                processcompletioncount++;
            }
            else
            {
                processes[min].remaining_time -= 1;
            }
        }
        else
        {
            timeline++;
        }
    }

    // Calculate the turnaround times.
    double avgtat = 0, avgwt = 0;
    for (int i = 0; i < num_processes; i++)
    {
        avgtat += processes[i].Tat;
        avgwt += processes[i].waiting_time;
    }
    avgtat = avgtat / num_processes;
    avgwt = avgwt / num_processes;
    printf("Average waiting time: %f\n", avgwt);
    printf("Average turnaround time: %f\n", avgtat);
}

void Priority_NP(struct process *processes, int num_processes)
{
    // Initialize the waiting times.
    int waiting_times[num_processes];
    for (int i = 0; i < num_processes; i++)
    {
        processes[i].waiting_time = 0;
        processes[i].Tat = 0;
        processes[i].Ct = 0;
    }

    // Calculate the waiting times.
    int min = 0;
    int prevmin = -1;
    int timeline = 0;
    for (int i = 0; i < num_processes; i++)
    {
        for (int j = 0; j < num_processes; j++)
        {
            if (processes[min].Ct != 0)
            {
                for (int x = 0; x < num_processes; x++)
                {
                    if (processes[j].Ct == 0)
                    {
                        min = j;
                        break;
                    }
                }
            }

            if (processes[min].priority >= processes[j].priority && processes[j].Ct == 0 && processes[j].arrival_time <= timeline)
            {
                prevmin = min;
                min = j;
            }
        }
        // printf("\n Process %d %d %d", min, processes[min].burst_time, processes[min].Ct);
        timeline += processes[min].burst_time;
        processes[min].Ct = timeline;
        processes[min].Tat = processes[min].Ct - processes[min].arrival_time;
        processes[min].waiting_time = processes[min].Tat - processes[min].burst_time;
        // printf("\n Process %d %d %d", min, processes[min].Tat, processes[min].waiting_time);
    }

    // Calculate the turnaround times.
    double avgtat = 0, avgwt = 0;
    for (int i = 0; i < num_processes; i++)
    {
        avgtat += processes[i].Tat;
        avgwt += processes[i].waiting_time;
    }
    avgtat = avgtat / num_processes;
    avgwt = avgwt / num_processes;
    printf("Average waiting time: %f\n", avgwt);
    printf("Average turnaround time: %f\n", avgtat);
}

void Priority_P(struct process *processes, int num_processes)
{
    // Initialize the waiting times.
    int waiting_times[num_processes];
    int Totalbt = 0;
    for (int i = 0; i < num_processes; i++)
    {
        processes[i].waiting_time = 0;
        processes[i].Tat = 0;
        processes[i].Ct = 0;
        processes[i].remaining_time = processes[i].burst_time;
        Totalbt += processes[i].burst_time;
    }

    // Calculate the waiting times.
    int min = 0;
    int timeline = 0;
    bool found = false;
    int processcompletioncount = 0;
    while (timeline < Totalbt)
    {
        found = false;
        for (int j = 0; j < num_processes; j++)
        {
            if (processes[j].arrival_time <= timeline && processes[j].Ct == 0)
            {
                found = true;
                for (int x = 0; x < num_processes; x++)
                {
                    if (processes[j].Ct == 0)
                    {
                        min = j;
                        break;
                    }
                }
                if (processes[min].priority > processes[j].priority && processes[j].Ct == 0 && processes[j].arrival_time <= timeline)
                {
                    min = j;
                }
            }
        }
        if (found)
        {
            timeline += 1;
            if (processes[min].remaining_time == 1)
            {
                processes[min].remaining_time -= 1;
                processes[min].Ct = timeline;
                processes[min].Tat = processes[min].Ct - processes[min].arrival_time;
                processes[min].waiting_time = processes[min].Tat - processes[min].burst_time;
                processcompletioncount++;
            }
            else
            {
                processes[min].remaining_time -= 1;
            }
        }
        else
        {
            timeline++;
        }
    }

    // Calculate the turnaround times.
    double avgtat = 0, avgwt = 0;
    for (int i = 0; i < num_processes; i++)
    {
        avgtat += processes[i].Tat;
        avgwt += processes[i].waiting_time;
    }
    avgtat = avgtat / num_processes;
    avgwt = avgwt / num_processes;
    printf("Average waiting time: %f\n", avgwt);
    printf("Average turnaround time: %f\n", avgtat);
}

void RoundRobin(struct process *processes, int num_processes, int timeQuantum)
{
    // Initialize the waiting times.
    struct Dqueue que;
    init(&que, 30);
    int waiting_times[num_processes];
    int Totalbt = 0;
    for (int i = 0; i < num_processes; i++)
    {
        processes[i].waiting_time = 0;
        processes[i].Tat = 0;
        processes[i].Ct = 0;
        processes[i].remaining_time = processes[i].burst_time;
        Totalbt += processes[i].burst_time;
        processes[i].inqueue = -1;
    }

    char gantt[30][10];
    int ganttptr=0;
    char gantt2[30][10];
    int ganttptr2=0;
    // Calculate the waiting times.
    int min = 0;
    int timeline = 0;
    bool found = true;
    int processcompletioncount = 0;
    while (timeline < Totalbt)
    {
        found = true;
        while (found)
        {
            found = false;   
            for (int j = 0; j < num_processes; j++)
            {
                
                if (processes[j].arrival_time <= timeline && processes[j].inqueue == -1)
                {
                    found = true;
                    if(processes[min].inqueue == 1){
                        for (int x = 0; x < num_processes; x++)
                    {
                        if (processes[j].inqueue == -1)
                        {
                            min = x;
                            break;
                        }
                    }
                    }
                    if (processes[min].arrival_time > processes[j].arrival_time && processes[j].inqueue == -1)
                    {
                        min = j; 
                    }
                }
            }
            if(found){
                if(min != -1){
                    processes[min].inqueue = 1;
                insertFromRear(&que, min);
                
                //printf("\n Process %d",min);
                min = -1;
                }
            }
        }

        if (!isEmpty(que))
        {
            int ele = deleteFromFront(&que);
            //printf("\n **Process %d %d",processes[ele].remaining_time,ele);
            if(processes[ele].remaining_time < timeQuantum){
                timeline += processes[ele].remaining_time;
                processes[ele].remaining_time = 0;
                sprintf(gantt[ganttptr],"P%d",ele);
                ganttptr++;
        sprintf(gantt2[ganttptr2],"%d",timeline);\
        ganttptr2++;

            }
            if(processes[ele].remaining_time >= timeQuantum){
                timeline += timeQuantum;
                processes[ele].remaining_time -= timeQuantum;
                sprintf(gantt[ganttptr],"P%d",ele);
                ganttptr++;
        sprintf(gantt2[ganttptr2],"%d",timeline);
        ganttptr2++;
                if(processes[ele].remaining_time > 1){
                    insertFromRear(&que, ele);
                }
                
            }
            
            if(processes[ele].remaining_time == 0){
                processes[ele].Ct = timeline;
                processes[ele].Tat = processes[ele].Ct - processes[ele].arrival_time;
                processes[ele].waiting_time = processes[ele].Tat - processes[ele].burst_time;
               // printf("\n\t ****Tat %d %d ct %d",processes[ele].Tat,ele,processes[ele].Ct);
            }
            
        }
    }

    // Calculate the turnaround times.
    double avgtat = 0, avgwt = 0;
    for (int i = 0; i < num_processes; i++)
    {
        avgtat += processes[i].Tat;
        avgwt += processes[i].waiting_time;
    }
    avgtat = avgtat / num_processes;
    avgwt = avgwt / num_processes;
    printf("Gantt chart:\n");
     for(int x=0;x<ganttptr;x++){
        printf("| %s |",gantt[x]);
        if(x+1 != ganttptr){
            printf(" ---- ");
        }
    }
    printf("\n");
     for(int x=0;x<ganttptr2;x++){
        printf("  %s  ",gantt2[x]);
        if(x+1 != ganttptr2){
            printf(" ---- ");
        }
    }
     printf("\n");
    printf("Average waiting time: %f\n", avgwt);
    printf("Average turnaround time: %f\n", avgtat);
}

int main()
{
    struct process processes_sjf[] =
        {{19, 0, 3},
            {10, 2, 2},
            {7, 4, 1}, };
    struct process precesses_temp[] = {
        {5, 0, 1},
        {3, 1, 2},
        {2, 2, 3},
        {6, 3, 4}};
    struct process precesses_fcfs[] =
        {{6, 1,1},
        {9, 4,1},
        {12, 0,1}};
    struct process precesses_Priority[] = {
        {10, 0, 3},
        {1, 0, 1},
        {2, 0, 4},
        {1, 0, 5},
        {5, 0, 2}};
    struct process precesses_RoundRobin[] = {
        {53, 0, 3},
        {17, 0, 1},
        {68, 0, 4},
        {24, 0, 5},
        };   
        
    int num_processes = sizeof(precesses_RoundRobin) / sizeof(precesses_RoundRobin[0]);
    
    printf("\n***** Fcfs *****\n");
     printf("\nProcess no | Burst Time | Arrival time | Priority");
    for(int x=0;x<sizeof(precesses_fcfs) / sizeof(precesses_fcfs[0]);x++){
        printf("\nP%d\t\t%d\t\t%d\t\t%d",x,precesses_fcfs[x].burst_time,precesses_fcfs[x].arrival_time,precesses_fcfs[x].priority);
    }    
    printf("\n");
    fcfs(precesses_fcfs, sizeof(precesses_fcfs) / sizeof(precesses_fcfs[0]));
    
    printf("\n***** SJF Preemptive ******\n");
     printf("\nProcess no | Burst Time | Arrival time | Priority");
    for(int x=0;x<sizeof(processes_sjf) / sizeof(processes_sjf[0]);x++){
        printf("\nP%d\t\t%d\t\t%d\t\t%d",x,processes_sjf[x].burst_time,processes_sjf[x].arrival_time,processes_sjf[x].priority);
    }    
    printf("\n");
    SJF_P(processes_sjf, sizeof(processes_sjf) / sizeof(processes_sjf[0]));
    printf("\n****** SJF Non-Preemptive******\n");
     printf("\nProcess no | Burst Time | Arrival time | Priority");
    for(int x=0;x<sizeof(processes_sjf) / sizeof(processes_sjf[0]);x++){
        printf("\nP%d\t\t%d\t\t%d\t\t%d",x,processes_sjf[x].burst_time,processes_sjf[x].arrival_time,processes_sjf[x].priority);
    }    
    printf("\n");
    SJF_NP(processes_sjf, sizeof(processes_sjf) / sizeof(processes_sjf[0]));
    printf("\n****** Priority Preemptive ******\n");
     printf("\nProcess no | Burst Time | Arrival time | Priority");
    for(int x=0;x<sizeof(processes_sjf) / sizeof(processes_sjf[0]);x++){
        printf("\nP%d\t\t%d\t\t%d\t\t%d",x,processes_sjf[x].burst_time,processes_sjf[x].arrival_time,processes_sjf[x].priority);
    }    
    printf("\n");
    Priority_P(processes_sjf, sizeof(processes_sjf) / sizeof(processes_sjf[0]));
    printf("\n***** Priority Non-Preemptive *****\n");
     printf("\nProcess no | Burst Time | Arrival time | Priority");
    for(int x=0;x<sizeof(processes_sjf) / sizeof(processes_sjf[0]);x++){
        printf("\nP%d\t\t%d\t\t%d\t\t%d",x,processes_sjf[x].burst_time,processes_sjf[x].arrival_time,processes_sjf[x].priority);
    }    
    printf("\n");
    Priority_NP(processes_sjf, sizeof(processes_sjf) / sizeof(processes_sjf[0]));
    printf("\n***** RoundRobin *****\n");
     printf("\nProcess no | Burst Time | Arrival time | Priority");
    for(int x=0;x<sizeof(precesses_RoundRobin) / sizeof(precesses_RoundRobin[0]);x++){
        printf("\nP%d\t\t%d\t\t%d\t\t%d",x,precesses_RoundRobin[x].burst_time,precesses_RoundRobin[x].arrival_time,precesses_RoundRobin[x].priority);
    }    
    printf("\n");
    RoundRobin(precesses_RoundRobin, num_processes,20);
    //   for(int x=0;x<num_processes;x++){
    //     printf("\nProcess %d -- Wt %d -- Bt %d -- Tat %d -- ct %d --",x,processes[x].waiting_time,processes[x].burst_time,processes[x].Tat,processes[x].Ct);
    //   }

    return 0;
}
