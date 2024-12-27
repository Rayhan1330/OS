#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>

int main(void){
    int key = 200;
    sem_t *mutex;
    sem_t *empty;
    sem_t *full;
    sem_t *smutex;
    int segid,lenid,emid,fid,mutid,sid;
    segid = shmget(key,100,IPC_CREAT|0644);
    lenid = shmget(key+1,100,IPC_CREAT|0644);
    emid = shmget(key+2,100,IPC_CREAT|0644);
    fid = shmget(key+3,100,IPC_CREAT|0644);
    mutid = shmget(key+4,100,IPC_CREAT|0644);
//sid = shmget(key+5,100,IPC_CREAT|0644);
    char *buff = shmat(segid,NULL,0);
    int *slen = shmat(lenid,NULL,0);
    empty = shmat(emid,NULL,0);
    full = shmat(fid,NULL,0);
    mutex = shmat(mutid,NULL,0);
    smutex = shmat(sid,NULL,0);
    sem_init(empty,1,*slen);
    sem_init(full,1,0);
    sem_init(mutex,1,1);
    //sem_init(smutex,1,1);
    //sem_wait(smutex);
    printf("Enter string: ");
    scanf("%s",buff);
    *slen = strlen(buff);
    //sem_post(smutex)
    int i=0;
    while(1){
        if(i>=*slen){
            printf("\nProducer over\n");
            break;
        }
        printf("Producer acquiring empty\n");
        sem_wait(empty);
        printf("Producer acquiring mutex\n");
        sem_wait(mutex);
        printf("%c",buff[i++]);
        printf("Producer releasing mutex\n")
        sem_post(mutex);
        sem_post(full);
    }
    shmdt(buff);
    shmdt(slen);
    shmdt(empty);
    shmdt(full);
    shmdt(mutex);
    
}
