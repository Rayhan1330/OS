#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int min= 9999;
int max = 0;
double avg = 0;
int count;
int *nums;

void *minimum(void *arr){
    for(int i=0;i<count;i++){
        if(min>nums[i]) min = nums[i];
    }
    pthread_exit(NULL);
}

void *average(void *arr){
    int sum = 0;
    for(int i=0;i<count;i++){
        sum+=nums[i];
    }
    avg = sum/count;
    pthread_exit(NULL);
}

void *maximum(void *arr){
    for(int i=0;i<count;i++){
        if(max<nums[i]) max = nums[i];
    }
    pthread_exit(NULL);
}

int main(int argc,char *argv[]){
    count = argc - 1;
    nums = (int *)malloc(sizeof(int)*count);
    for(int i=0;i<count;i++){
        nums[i] = atoi(argv[i+1]);
    }
    pthread_t threads[3];
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;
    pthread_create(&threads[1],NULL,minimum,t1);
    pthread_create(&threads[2],NULL,average,t2);
    pthread_create(&threads[3],NULL,maximum,t3);
    for(int i=0;i<count;i++){
        pthread_join(&threads[i],NULL);
    }
    printf("Minimum: %d\n",min);
    printf("Average: %f\n",avg);
    printf("Maximum: %d\n",max);
}
