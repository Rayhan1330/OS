#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

typedef struct ll{
    char fname[30];
    char buff[100];
    int status;
}shared;

int main(void){
    int key = 200;
    int shmid = shmget(key,100,IPC_CREAT|0644);
    shared *s = shmat(shmid,NULL,0);
    while(strcmp(s->fname,"")==0){
        continue;
    }
    printf("File name from server: %s",s->fname);
    int fd = open(s->fname,O_RDONLY);
    if(fd==-1){
        s->status = -1;
        exit(1);
    }
    int i = 0;
    int re = 1;
    char *c = (char *)malloc(sizeof(char));
    while(re>0){
        re = read(fd,c,1);
        s->buff[i++] = c[0];
    }
    shmdt(s);
}
