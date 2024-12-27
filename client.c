#include <stdio.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

typedef struct ll{
    char fname[30];
    char buff[100];
    int status;
}shared;

int main(void){
    int key = 200;
    shared *s;
    char *str;
    int shmid = shmget(key,100,IPC_CREAT|0644);
    s = shmat(shmid,NULL,0);
    printf("Enter filename: ");
    scanf("%s",str);
    strcpy(s->fname,str);
    while(s->status==0){
        continue;
    }
    if(s->status == -1){
        printf("Error\n");
        exit(1);
    }
    printf("%s",s->buff);
    shmdt(s);
    shmctl(shmid,IPC_RMID,NULL);
}
