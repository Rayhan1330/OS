#include <stdio.h>
#include <stdlib.h>

typedef struct task_schedule{
    int at; //arrival time
    int bt; //burst time
    int st; //start time
    int et; //end time
    int wt; //wait time
    int tt; //turn around time
    int rt; //response time
    int com;
}task;

void display(task **arr,int n){
    for(int i=0;i<n;i++){
        printf("AT  BT  ST  ET  WT  RT  TT\n");
        printf("%3d %3d %3d %3d %3d %3d %3d\n",arr[i]->at,arr[i]->bt,arr[i]->st,arr[i]->et,arr[i]->wt,arr[i]->rt,arr[i]->tt);
    }
}

void npsjf(task **arr,int n){
    int clk = 0;
    int sum_bt = 0;
    for(int i=0;i<n;i++)
        sum_bt += arr[i]->bt;
    printf("%d\n",sum_bt);
    while(clk<=sum_bt){
        int sjf_ind;
        for(int i=0;i<n;i++){
            if(arr[i]->com==0){
                sjf_ind = i;
                break;
            }
        }
        for(int i=0;((i<n) && (arr[i]->at<=clk) && (arr[i]->com==0));i++){
            if(arr[i]->bt<arr[sjf_ind]->bt && arr[i]->at<=clk)
                sjf_ind = i;
        }
        arr[sjf_ind]->st = clk;
        clk = clk + arr[sjf_ind]->bt;
        arr[sjf_ind]->et = clk;
        arr[sjf_ind]->wt = arr[sjf_ind]->st - arr[sjf_ind]->at;
        arr[sjf_ind]->tt = arr[sjf_ind]->et - arr[sjf_ind]->at;
        arr[sjf_ind]->rt = arr[sjf_ind]->st - arr[sjf_ind]->at;
        arr[sjf_ind]->com = 1;
        printf("%d\n",clk);
    }
}

void fcfs(task **arr,int n){
    int clk = 0;
    int sum_bt = 0;
    for(int i=0;i<n;i++)
        sum_bt += arr[i]->bt;
    printf("%d\n",sum_bt);
    while(clk!=sum_bt){
        int fcfs_ind;
        for(int i=0;i<n;i++){
            if(arr[i]->com==0){
                fcfs_ind = i;
                break;
            }
        }
        for(int i=0;((i<n) && (arr[i]->at<=clk) && (arr[i]->com==0));i++){
            if(arr[i]->at<arr[fcfs_ind]->at && arr[i]->at<=clk)
                fcfs_ind = i;
        }
        arr[fcfs_ind]->st = clk;
        clk = clk + arr[fcfs_ind]->bt;
        arr[fcfs_ind]->et = clk;
        arr[fcfs_ind]->wt = arr[fcfs_ind]->st - arr[fcfs_ind]->at;
        arr[fcfs_ind]->tt = arr[fcfs_ind]->et - arr[fcfs_ind]->at;
        arr[fcfs_ind]->rt = arr[fcfs_ind]->st - arr[fcfs_ind]->at;
        arr[fcfs_ind]->com = 1;
        printf("%d\n",clk);
    }
}


void calculation(task **arr,int n){
    float sum_wt = 0;
    float sum_tt = 0;
    float sum_rt = 0;
    for(int i=0;i<n;i++){
        sum_tt += arr[i]->tt;
        sum_wt += arr[i]->wt;
        sum_rt += arr[i]->rt;
    }
    printf("Average waiting time: %f\n",sum_wt/n);
    printf("Average turn around time: %f\n",sum_tt/n);
    printf("Average response time: %f\n",sum_rt/n);
}

int main(void){
    int n;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    task **arr = (task **)malloc(n*sizeof(task));
    for(int i=1;i<=n;i++){
        arr[i-1] = (task *)malloc(sizeof(task));
        printf("\n\nFOR PROCESS %d\n",i);
        printf("Enter arrival time: ");
        scanf("%d",&arr[i-1]->at);
        printf("Enter burst time: ");
        scanf("%d",&arr[i-1]->bt);
        arr[i-1]->com = 0;
    }
    npsjf(arr,n);
    //fcfs(arr,n);
    display(arr,n);
    calculation(arr,n);
}
