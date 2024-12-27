#include <stdio.h>
#include <stdlib.h>

typedef struct p{
    int id;
    int at;
    int bt;
    int st;
    int et;
    int wt;
    int tt;
    int rt;
    int prio;
    int com;
}node;

void display(node **p,int n){
    for(int i=0;i<n;i++){
        printf("\nProcess ID: %d\n",p[i]->id);
        printf("Starting Time: %d\n",p[i]->st);
        printf("Ending Time: %d\n",p[i]->et);
        printf("Waiting Time: %d\n",p[i]->wt);
        printf("Turnaround Time: %d\n",p[i]->tt);
        printf("Response Time: %d\n",p[i]->rt);
    }
}

int main(void){
    int n;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    node **p = (node **)malloc(sizeof(node *));
    for(int i=0;i<n;i++){
        p[i] = (node *)malloc(sizeof(node));
        printf("Enter process ID: ");
        scanf("%d",&p[i]->id);
        printf("Enter arrival time: ");
        scanf("%d",&p[i]->at);
        printf("Enter burst time: ");
        scanf("%d",&p[i]->bt);
        printf("Enter priority: ");
        scanf("%d",&p[i]->prio);
        p[i]->com = 0;
        p[i]->st = -1;
        p[i]->wt = -1;
    }
    int clk = 0;
    int no_of_processes = 0;
    while(no_of_processes!=n){
        int min = 9999;
        int min_ind;
        for(int i=0;i<n;i++){
            if(p[i]->prio<min && p[i]->at<=clk && p[i]->com == 0){
                min = p[i]->prio;
                min_ind = i;
            }
        }
        if(p[min_ind]->st==-1)
            p[min_ind]->st = clk;
        if(p[min_ind]->wt == -1)
            p[min_ind]->wt = p[min_ind]->st - p[min_ind]->at;
        else
            p[min_ind]->wt += clk - p[min_ind]->et;
        p[min_ind]->bt--;
        clk++;
        p[min_ind]->et = clk;
        if(p[min_ind]->bt == 0){
            p[min_ind]->com = 1;
            p[min_ind]->tt = p[min_ind]->et - p[min_ind]->at;
            p[min_ind]->rt = p[min_ind]->st - p[min_ind]->at;
            no_of_processes++;
        }
    }
    display(p,n);
}
