#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <signal.h>

typedef struct mm{
    char msg[20];
    char status[20];
    int pid_client;
    int pid_server;
}shared;

shared *s;

void handler(int signo){
    if(signo == SIGUSR1 && strcmp(s->status,"READY")==0){
        printf("Message received from Client: %s\n",s->msg);
        strcpy(s->status,"NOTREADY");
    }
}

int main(void){
    int key = 300;
    int shmid = shmget(key,100,0);
    s = shmat(shmid,NULL,0);
    s->pid_server = getpid();
    strcpy(s->status,"NOTREADY");
    while(strcmp(s->status,"NOTREADY")==0)
        continue;
    signal(SIGUSR1,handler);
    char *message = malloc(sizeof(char)*100);
    while(1){
        printf("Enter message: ");
        scanf("%s",message);
        sleep(5);
        strcpy(s->msg,message);
        strcpy(s->status,"FILLED");
        if(kill(s->pid_client,SIGUSR2)==-1){
            printf("Error\n");
            exit(1);
        }
        while(strcmp(s->status,"FILLED")==0)
            continue;
        if(strcmp(s->status,"exit")==0)
            exit(1);
    }
    shmdt(s);
    shmctl(shmid,IPC_RMID,NULL);
}
