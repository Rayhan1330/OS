#include <stdio.h>
#include <stdlib.h>

typedef struct linked{
    int *arr;
    struct linked *next;
}link;

void insert(link *head,link *sub){
    link *temp = head;
    while(temp->next!=NULL) temp = temp->next;
    temp->next = sub;
}

int in_array(int *arr,int e,int n){
    for(int i=0;i<n;i++){
        if(arr[i]==e) return i+1;
    }
    return 0;
}

int main(void){
    int n,c,nf;
    printf("Enter number of frames: ");
    scanf("%d",&nf);
    printf("Enter the number of references: ");
    scanf("%d",&n);
    int *arr = (int *)malloc(sizeof(int)*n);
    link *head = NULL;
    for(int i=0;i<n;i++){
        printf("Enter reference: ");
        scanf("%d",&arr[i]);
        link *node = (link *)malloc(sizeof(link));
        node->arr = (int *)malloc(sizeof(int)*nf);
        for(int i=0;i<nf;i++){
            node->arr[i] = -1;
        }
        node->next = NULL;
        if(head==NULL) head = node;
        else insert(head,node);
    }
    printf("Enter paging algorithm: \n");
    printf("1.FIFO\n");
    printf("2.LRU \n");
    printf("3.Optimal \n");
    printf("Enter your choice: ");
    scanf("%d",&c);
    int pf = 0; //number of page faults
    if(c==1){//fifo
        printf("This is FIFO Algorithm\n");
        for(int i = 0;i<n;i++){
            link *temp = head;
            if(i==0){
                head->arr[0] = arr[0];
                pf++;
                printf("Page fault \n");
            }
            else{
                for(int j = 0;j<i-1;j++) temp = temp->next;
                if(in_array(temp->arr,arr[i],nf)){
                    printf("No page fault\n");
                    link *temp1 = temp->next;
                    temp1->arr = temp->arr;
                }
                else{
                    pf++;
                    int chk=0;
                    link *temp1 = temp->next;
                    temp1->arr = temp->arr;
                    for(int j=0;j<nf;j++){
                        if(!in_array(arr,temp->arr[j],n)){
                            //printf("%d %d\n",in_array(arr,temp->arr[j],n),temp->arr[j]);
                            temp1->arr[j] = arr[i];
                            chk=1;
                            break;
                        }
                        
                        
                    }
                    if(chk==0){
                        int min = 9999;
                        int min_ind;
                        for(int j=0;j<nf;j++){
                            for(int k=0;k<n;k++){
                                if(arr[k]==temp->arr[j]){
                                    if(k<min){
                                        min = k;
                                        min_ind = j;
                                    }
                                }
                            }
                        }
                        temp1->arr[min_ind] = arr[i];
                        
                    }
                    printf("Page fault \n");
                }
            }
            printf("Frames\n");
            for(int i=0;i<nf;i++){
                if(temp->arr[i]!=-1)
                    printf("%d ",temp->arr[i]);
            }
            printf("\n");
            
        }
    }
    if(c==2){//LRU
        printf("This is LRU Algorithm\n");
        for(int i = 0;i<n;i++){
            link *temp = head;
            if(i==0){
                head->arr[0] = arr[0];
                pf++;
                printf("Page fault \n");
            }
            else{
                for(int j = 0;j<i-1;j++) temp = temp->next;
                if(in_array(temp->arr,arr[i],nf)){
                    printf("No page fault\n");
                    link *temp1 = temp->next;
                    temp1->arr = temp->arr;
                }
                else{
                    pf++;
                    int chk=0;
                    link *temp1 = temp->next;
                    temp1->arr = temp->arr;
                    for(int j=0;j<nf;j++){
                        if(!in_array(arr,temp->arr[j],n)){
                            //printf("%d %d\n",in_array(arr,temp->arr[j],n),temp->arr[j]);
                            temp1->arr[j] = arr[i];
                            chk=1;
                            break;
                        }
                        
                        
                    }
                    if(chk==0){
                        int min = 9999;
                        int min_ind;
                        for(int j = 0;j<nf;j++){
                            for(int k = 0;k<i;k++){
                                if(arr[k] == temp1->arr[j]){
                                    if(k<=min){
                                        min = k;
                                        min_ind = j;
                                    }
                                }
                                    
                            }
                        }
                        temp1->arr[min_ind] = arr[i];
                        
                    }
                    printf("Page fault \n");
                }
            }
            printf("Frames\n");
            for(int i=0;i<nf;i++){
                if(temp->arr[i]!=-1)
                    printf("%d ",temp->arr[i]);
            }
            printf("\n");
            
        }
    }
    if(c==3){//Optimal
        printf("This is Optimal Algorithm\n");
        for(int i = 0;i<n;i++){
            link *temp = head;
            if(i==0){
                head->arr[0] = arr[0];
                pf++;
                printf("Page fault \n");
            }
            else{
                for(int j = 0;j<i-1;j++) temp = temp->next;
                if(in_array(temp->arr,arr[i],nf)){
                    printf("No page fault\n");
                    link *temp1 = temp->next;
                    temp1->arr = temp->arr;
                }
                else{
                    pf++;
                    int chk=0;
                    link *temp1 = temp->next;
                    temp1->arr = temp->arr;
                    for(int j=0;j<nf;j++){
                        if(!in_array(arr,temp->arr[j],n)){
                            //printf("%d %d\n",in_array(arr,temp->arr[j],n),temp->arr[j]);
                            temp1->arr[j] = arr[i];
                            chk=1;
                            break;
                        }
                        
                        
                    }
                    if(chk==0){
                        int max = 0;
                        int max_ind;
                        for(int j = 0;j<nf;j++){
                            int chk = 0; //flag
                            for(int k = i+1;k<n;k++){
                                if(arr[k] == temp1->arr[j]){
                                    chk = 1;
                                    if(k>=max){
                                        max = k;
                                        max_ind = j;
                                    }
                                }
                                
                            }
                            if(chk == 0){
                                max = 9999;
                                max_ind = j;
                            }
                        }
                        temp1->arr[max_ind] = arr[i];
                        
                    }
                    printf("Page fault \n");
                }
                printf("Frames\n");
                for(int i=0;i<nf;i++){
                    if(temp->arr[i]!=-1)
                        printf("%d ",temp->arr[i]);
                }
                printf("\n");
                
            }
        }
    }
        
}
