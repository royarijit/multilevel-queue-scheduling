#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Declaring the components of a process using a structure type of data
//pid is process id
//priority is the priority of the process in an integer value
//bt is the burst time of the process
//at is the arrival time of the process
//wt is the waiting time of the process
//tt is the turnaround time of the process
struct process{
    int pid,priority,bt,at,wt,tt,rt;
};

//Declaration of the function that will take user input about the various data related to the process
void input_data();

//Declaring a function that will calculate waiting time and the turn around time of the processes
void waiting_time(struct process *q,int);
void turnaround_time(struct process *q,int);

void round_robin();
void priority_scheduling();
void fcfs();


void printQueueI(struct process);
void printQueue(struct process *,int);

//Queues
//Q1 = Batch Process having Low Priority with FCFS Algorithm
//Q2 = Interactive Process having Medium Priority with Priority Based Sorting
//Q3 = System Process having High Priority with Round Robin Algorith Quantum Time=4
int q1_n=0,q2_n=0,q3_n=0,n=0; //N=Total Process
struct process *q1,*q2,*q3;
//Time Quantum
int time_quantum = 4;


void input_data(){
    printf("\n Total Number of Process:\t");
    scanf("%d",&n);
    //Allocatig Memory
    q1 = (struct process *)malloc(n*sizeof(struct process));
    q2 = (struct process *)malloc(n*sizeof(struct process));
    q3 = (struct process *)malloc(n*sizeof(struct process));
    for(int i=0;i<n;i++){
        struct process p;
        printf("\n\t\tProcess %d\n=============================================\n\n",i+1);
        printf("PId:\t");
        scanf("%d",&p.pid);
        printf("Arival time:");
        scanf("%d",&p.at);
        printf("Priority (1-9):\t");
        scanf("%d",&p.priority);
        printf("\nBurst Time:\t");
        scanf("%d",&p.bt);
        p.rt = p.bt;
        if(p.priority>0 && p.priority<=3){
            q1[q1_n++]  = p;
        }else if(p.priority>3 && p.priority<=6){
            q2[q2_n++] = p;
        }else{
            q3[q3_n++] = p;
        }
    }
}
void printQueue(struct process *q,int size){
    waiting_time(q,size);
    turnaround_time(q,size);
    printf("\nPId\t\tPriority\t\tBurst Time\t\tWaiting Time\t\tTurnAround Time\t\tArrival");
    printf("\n================================================================================\n");
    for(int i=0;i<size;i++){
        printQueueI(q[i]);
    }
    printf("\n\n");
}
void printQueueI(struct process p){
    printf("\n%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t%d",p.pid,p.priority,p.bt,p.wt,p.tt,p.at);
}
void waiting_time(struct process *q,int size){
    q[0].wt = 0;
    for(int i=1;i<size;i++){
        q[i].wt = q[i-1].wt + q[i-1].bt;
    }
}
void turnaround_time(struct process *q,int size){
    q[0].wt = 0;
    for(int i=0;i<size;i++){
        q[i].tt = q[i].wt + q[i].bt;
    }
}
void RoundRobinAlgo(struct process *q,int size){
    int time=0,i=0,remain=size,flag=0,wait_time=0,tat_time=0,total_times=0;
    for(time=0,i=0;remain!=0;){
        struct process p = q[i];
        if(p.rt<=time_quantum && p.rt>0){
            time += p.rt;
            p.rt = 0;
            flag = 1;
        }else if(p.rt>time_quantum){
            p.rt -= time_quantum;
            time += time_quantum;
        }
        if(p.rt==0 && flag==1){
            remain--;
            printf("\n%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d",p.pid,p.priority,p.bt,p.wt,p.tt);
            wait_time += time -p.at - p.bt;
            tat_time += time -p.at;
            flag = 0;
        }

        if(i==remain-1){
            i=0;
        }else if(q[i+1].at<time){
            i++;
        }else{
            i=0;
        }

        q[i] = p;
    }
    printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n);
    printf("Avg Turnaround Time = %f\n",tat_time*1.0/n);
}
void round_robin(){
    printf("\n\n===========================================================================");
    printf("\n\t\tRound Robin\t");
    printf("\n===========================================================================\n\n");

    printf("\nPId\t\tPriority\t\tBurst Time\t\tWaiting Time\t\tTurnAround Time");
    printf("\n================================================================================\n");
    waiting_time(q3,q3_n);
    turnaround_time(q3,q3_n);

    RoundRobinAlgo(q3,q3_n);
}
void PrioSortingAlgorithm(struct process *q,int size){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(q[j].priority>q[i].priority){
                struct process t = q[i];
                q[i] = q[j];
                q[j] = t;
            }
        }
    }
}
void priority_scheduling(){
    printf("\n\n===========================================================================");
    printf("\n\t\tPriority Sorting\t");
    printf("\n===========================================================================\n\n");
    PrioSortingAlgorithm(q2,q2_n);
    printQueue(q2,q2_n);
}
void FCFSAlgorithm(struct process *q,int size){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(q[j].at>q[i].at){
                struct process t = q[i];
                q[i] = q[j];
                q[j] = t;
            }
        }
    }
}
void fcfs(){
    printf("\n\n===========================================================================");
    printf("\n\t\tFirst Come First Serve\t");
    printf("\n===========================================================================\n\n");
    FCFSAlgorithm(q1,q1_n);
    printQueue(q1,q1_n);
}
int main(){
    input_data();
    int i=1;
    for(i=1;i<=3;i++){
        switch(i){
            case 3:
                round_robin();
                break;
            case 2:
                priority_scheduling();
                break;
            case 1:
                fcfs();
                break;
            default:
                printf("done");
        }

    }
    printf("\n\n");
}
