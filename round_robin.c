#include <stdio.h>
#include <stdlib.h>

typedef struct process{
    int at;
    int bt;
    int st;
    int et;
    int wt;
    int tt;
    int rt;
    int com;
}node;

void display(node **p,int n){
    for(int i=0;i<n;i++){
        printf("Process P%d \n",i+1);
        printf("Arrival time: %d\n",p[i]->at);
        printf("Burst time: %d\n",p[i]->bt);
        printf("Start time: %d\n",p[i]->st);
        printf("End time: %d\n",p[i]->et);
        printf("Waiting time: %d\n",p[i]->wt);
        printf("Response time: %d\n",p[i]->rt);
        printf("Turnaround time: %d\n",p[i]->tt);
    }
}


void rr(node **p,int n){
    int clk = 0;
    int no_of_proc = 0;
    int arr[10000];
    for (int i=0;i<n;i++){
        arr[i] = i;
    }
    int q;
    printf("Enter time quantum: ");
    scanf("%d",&q);
    int i=0;
    while(1){
        int ind = arr[i];
        if(no_of_proc == n) break;
        if(p[ind]->st==0 && ind!=0){
            printf("Hi\n");
            p[ind]->st = clk;
        }
        if(ind==i){
            p[ind]->wt = p[ind]->st - p[ind]->at;
        }
        else{
            p[ind]->wt = clk - p[ind]->et + p[ind]->wt;
        }
            
        //printf("Hi\n");
        for(int j = 0;j<q;j++){
            //printf("Hi\n");
            p[ind]->bt = p[ind]->bt - 1;
            //printf("Burst time: %d\n",p[ind]->bt);
            clk++;
            if(p[ind]->bt==0){
                p[ind]->et = clk;
                p[ind]->com = 1;
                no_of_proc++;
                p[ind]->rt = p[ind]->st - p[ind]->at;
                p[ind]->tt = p[ind]->et - p[ind]->st;
                break;
            }
            
        }
        if(p[ind]->com==0){
            p[ind]->et = clk;
            //printf("index val: %d\n",i+n);
            arr[i+n] = ind;
        }
        i++;
    }
}

int main(void){
    int n;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    node **p = (node **)malloc(sizeof(node *)*n);
    for(int i=0;i<n;i++){
        p[i] = (node *)malloc(sizeof(node));
        printf("Enter Arrival time for process p%d: ",i+1);
        scanf("%d",&p[i]->at);
        printf("Enter Burst time for process p%d: ",i+1);
        scanf("%d",&p[i]->bt);
    }
    rr(p,n);
    display(p,n);
}
