#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct block{
    int id;
    char status[50];
    struct block *next;
    struct block *linked_next;
    int *index_arr;
}BLOCK;

void insert(BLOCK *head,BLOCK *sub){
    BLOCK *temp = head;
    while(temp->next!=NULL) temp = temp->next;
    temp->next = sub;
}

void display(BLOCK *head){
    BLOCK *temp = head;
    while(temp!=NULL){
        printf("Status: %s\n",temp->status);
        temp = temp->next;
    }
}

int main(void){
    int n,n1;
    printf("Enter size of main memory: ");
    scanf("%d",&n);
    printf("Enter block size: ");
    scanf("%d",&n1);
    int k = n/n1;
    BLOCK *head = NULL;
    for(int i=0;i<k;i++){
        BLOCK *node = (BLOCK *)malloc(sizeof(BLOCK));
        strcpy(node->status,"H");
        node->next = NULL;
        node->linked_next = NULL;
        node->id = i;
        if(head == NULL) head = node;
        else insert(head,node);
    }
    int nf;
    printf("Enter number of files: ");
    scanf("%d",&nf);
    char **arr = (char **)malloc(sizeof(char *)*nf);
    int *array = (int *)malloc(sizeof(int)*nf);
    for(int i=0;i<nf;i++){
        arr[i] = (char *)malloc(sizeof(char)*20);
        printf("Enter filename: ");
        scanf("%s",arr[i]);
        printf("Enter size of file: ");
        scanf("%d",&array[i]);
    }
    int choice;
    printf("Enter\n");
    printf("1.Contiguous allocation\n");
    printf("2.Linked allocation\n");
    printf("3.Indexed allocation\n");
    scanf("%d",&choice);
    if(choice==1){ //Contiguous Allocation
        for(int j = 0;j<nf;j++){
            int no_of_blocks = array[j]/n1;
            if(array[j]%n1>0) no_of_blocks++;
            BLOCK *temp;
            int randomno;
            while(1){
                randomno = rand() % k;
                randomno = randomno-1;
                temp = head;
                int flag = 0;
                for (int i=0;i<randomno;i++) temp = temp->next;
                for(int i=0;i<no_of_blocks;i++){
                    if(strcmp(temp->status,"H")!=0){
                        flag = 1;
                        break;
                    }
                    if(flag == 1) break;
                    temp = temp->next;
                }
                if(flag == 1) continue;
                else break;
            }
            temp = head;
            for (int i=0;i<randomno;i++) temp = temp->next;
            for(int i=0;i<no_of_blocks;i++){
                strcpy(temp->status,arr[j]);
                temp = temp->next;
            }
        }
        display(head);
        
    }
    if(choice == 2){ //Linked Allocation
        for(int j=0;j<nf;j++){
            int no_of_blocks = array[j]/n1;
            if(array[j]%n1!=0) no_of_blocks++;
            BLOCK *temp;
            int randno;
            BLOCK *sub = NULL;
            for(int k=0;k<no_of_blocks;k++){
                randno = rand() % (n/n1);
                temp = head;
                for(int l=0;l<randno;l++) temp = temp->next;
                if(strcmp(temp->status,"H")!=0){
                    no_of_blocks++;
                    continue;
                }
                else{
                    char *str = (char *)malloc(sizeof(char)*50);
                    str = arr[j] + k;
                    
                    if(sub == NULL){
                        strcpy(temp->status,arr[j]);
                        sub = temp;
                    }
                    else{
                        strcpy(temp->status,str);
                        sub->linked_next = temp;
                        sub = temp;
                    }
                }
            }
        }
        for(int j=0;j<nf;j++){ //to display
            BLOCK *temp = head;
            while(temp!=NULL){
                if(strcmp(temp->status,arr[j])==0){
                    BLOCK *temp1 = temp;
                    printf("%s: ",arr[j]);
                    while(temp1!=NULL){
                        printf("%d->",temp1->id);
                        temp1 = temp1->linked_next;
                    }
                    printf("\n");
                    break;
                }
                temp = temp->next;
            }
        }
    }
    if(choice == 3){ //Indexed Allocation
        for(int i=0;i<nf;i++){
            int no_of_blocks = array[i]/n1;
            if(array[i]%n1!=0) no_of_blocks++;
            BLOCK *first = NULL;
            int ind = 0;
            for(int j = 0;j<no_of_blocks;j++){
                int randno = rand() % k;
                BLOCK *temp = head;
                for(int s=0;s<randno;s++) temp = temp->next;
                if(strcmp(temp->status,"H")!=0){
                    no_of_blocks++;
                    continue;
                }
                else{
                    if(first == NULL){
                        strcpy(temp->status,arr[i]);
                        first = temp;
                        first->index_arr = (int *)malloc(sizeof(int)*(no_of_blocks));
                    }
                    else{
                        strcpy(temp->status,"index");
                        first->index_arr[ind++] = temp->id;
                    }
                }
            }
        }
        for(int i=0;i<nf;i++){
            BLOCK *temp1 = head;
            while(temp1!=NULL){
                if(strcmp(temp1->status,arr[i])==0){
                    printf("%d->{",temp1->id);
                    int n = array[i]/n1;
                    if(array[i]%n1!=0) n++;
                    n--;
                    for(int j = 0;j<n;j++)
                        printf("%d,",temp1->index_arr[j]);
                    printf("\n");
                    break;
                }
                temp1 = temp1->next;
            }
        }
        
    }
    
    //display(head);
}
