#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

int main(void){
    int key = 200;
    sem_t *mutex;
    sem_t *empty;
    sem_t *full;
    int segid,lenid,emid,fid,mutid;
    segid = shmget(key,100,0);
    lenid = shmget(key+1,100,0);
    emid = shmget(key+2,100,0);
    fid = shmget(key+3,100,0);
    mutid = shmget(key+4,100,0);
    char *buff = shmat(segid,NULL,0);
    empty = shmat(emid,NULL,0);
    full = shmat(fid,NULL,0);
    mutex = shmat(mutid,NULL,0);
    sleep(5);
    int *slen = shmat(lenid,NULL,0);
    printf("Length of string: %d",*slen);
    int i=0;
    while(1){
        if(i>=*slen){
            printf("\nConsumer process over\n");
            break;
        }
        printf("Consumer acquiring full\n");
        sem_wait(full);
        printf("Consumer acquiring mutex\n");
        sem_wait(mutex);
        printf("%c",buff[i++]);
        printf("Consumer releasing mutex\n");
        sem_post(mutex);
        sem_post(empty);
    }
    shmdt(buff);
    shmdt(slen);
    shmdt(empty);
    shmdt(full);
    shmdt(mutex);
    shmctl(segid,IPC_RMID,NULL);
    shmctl(lenid,IPC_RMID,NULL);
    shmctl(emid,IPC_RMID,NULL);
    shmctl(fid,IPC_RMID,NULL);
    shmctl(mutid,IPC_RMID,NULL);
    sem_destroy(empty);
    sem_destroy(full);
    sem_destroy(mutex);
}

