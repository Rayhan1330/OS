#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ll{
    int size;
    int status;
    struct ll *next;
}link;

void insert(link *head,link *node){
    link *temp = head;
    while(temp->next!=NULL) temp = temp->next;
    temp->next = node;
}

void display(link *head,int c){
    link *temp = head;
    
    while(temp!=NULL){
        if(temp->status == 0){
            if(c!=1){
                printf("Status: Hole\n");
                printf("Node size: %d\n",temp->size);
            }
        }
        else{
            if(c != 0){
                printf("Process ID: %d\n",temp->status);
                printf("Node size: %d\n",temp->size);
            }
        }
        temp = temp->next;
        printf("\n");
    }
    
}

int main(void){
    int n;
    link *free_space = NULL, *alloc = NULL, *copy = NULL;
    printf("Enter the number of partitions in memory: ");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        link *node = (link *)malloc(sizeof(link));
        printf("Enter size of hole %d: ",i+1);
        scanf("%d",&node->size);
        node->status = 0;
        node->next = NULL;
        if(free_space == NULL){
            free_space = node;
            //copy = node;
        }
        else{
            insert(free_space,node);
            //insert(copy,node);
        }
    }
    while(1){
        printf("1.First Fit\n");
        printf("2.Best Fit\n");
        printf("3.Worst Fit\n");
        printf("4.End\n");
        printf("\nEnter your choice: ");
        int choice;
        scanf("%d",&choice);
        if(choice==4) break;
        while(1){
            printf("\n1.Entry/Allocate\n");
            printf("2.Exit/Deallocate\n");
            printf("3.Display\n");
            printf("4.Coalescing Holes\n");
            printf("5.Back to Algorithm\n");
            int c;
            printf("\nEnter choice: ");
            scanf("%d",&c);
            link *temp;
            if(c==5){
                free(alloc);
                alloc = NULL;
                break;
            }
            if(c==1){
                link *node1 = (link *)malloc(sizeof(link));
                printf("Enter process ID: ");
                scanf("%d",&node1->status);
                printf("Enter size: ");
                scanf("%d",&node1->size);
                link *result = NULL;
                temp = free_space;
                while(temp!=NULL){ //First Fit
                    if(temp->size>=node1->size && temp->status == 0){
                        result = temp;
                        break;
                    }
                    temp = temp->next;
                }
                if(choice == 2){ //Best Fit
                    while(temp!=NULL){
                        if((temp->size<result->size) && (temp->size>= node1->size) && (temp->status == 0)){
                            result = temp;
                        }
                        temp = temp->next;
                    }
                }
                if(choice == 3){  //Worst Fit
                    while(temp!=NULL){
                        if((temp->size>result->size) && (temp->size>= node1->size) && (temp->status == 0)){
                            result = temp;
                        }
                        temp = temp->next;
                    }
                }
                if(result == NULL){
                    printf("Cannot accomodate. Try coalescing\n");
                    continue;
                }
                int diff = result->size - node1->size;
                if(diff == 0){
                    result->status = node1->status;
                    if(alloc == NULL) alloc = node1;
                    else insert(alloc,node1);
                }
                else{
                    link *new = (link *)malloc(sizeof(link));
                    new->status = 0;
                    new->size = diff;
                    result->size = node1->size;
                    new->next = result->next;
                    result->next = new;
                    result->status = node1->status;
                }
            }
            if(c == 2){
                int pid;
                printf("Enter Process ID: ");
                scanf("%d",&pid);
                temp = free_space;
                while(temp!=NULL){
                    if(temp->status == pid){
                        temp->status = 0;
                    }
                    temp = temp->next;
                }
            }
            if(c == 3){
                printf("\nFree Space\n\n");
                display(free_space,0);
                printf("\nAllocated Pool\n\n");
                display(free_space,1);
                printf("\nTotal Memory\n\n");
                display(free_space,2);
            }
            if(c==4){
                temp = free_space;
                while(temp->next!=NULL){
                    link *sub = temp->next;
                    if(temp->status == 0 && sub->status == 0){
                        temp->size += sub->size;
                        temp->next = sub->next;
                        free(sub);
                    }
                    else
                        temp = temp->next;
                }
            }
            
        }
        
    }
    
    return 0;
}
