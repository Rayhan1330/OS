#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int start;
    int end;
    int size;
    int status;
    struct node *next;
}NODE;

NODE *initialize(){
    NODE *list = (NODE *)malloc(sizeof(NODE));
    return list;
}

void insert(NODE *list,NODE *temp1){
    NODE *temp = list;
    while (temp->next!=NULL) temp = temp->next;
    temp->next = temp1;
}

void delete(NODE *list,NODE *sub){
    NODE *temp = list;
    while(temp->next!=sub) temp = temp->next;
    temp->next = sub->next;
    free(sub);
}

void display(NODE *list,char c){
    NODE *temp = list;
    while(temp!=NULL){
        if(c=='f'){
            if(temp->status!=0){
                temp = temp->next;
                continue;
            }
                
            printf("\nProcess ID/Status: H\n");
        }
        else{
            if(temp->status==0) printf("\nProcess ID/Status: H\n");
            else printf("\nProcess ID/Status: %d\n",temp->status);
        }
        printf("Starting address: %d\n",temp->start);
        printf("Starting address: %d\n",temp->end);
        temp = temp->next;
    }
}








int main(void){
    NODE *free_space=NULL;
    NODE *alloc1=NULL;
    NODE *alloc2=NULL;
    NODE *alloc3=NULL;
    int p;
    printf("Enter the number of partitions in memory: ");
    scanf("%d",&p);
    for(int i=0;i<p;i++){
        int s1,s2;
        NODE *space = (NODE *)malloc(sizeof(NODE));
        printf("Enter starting address: ");
        scanf("%d",&s1);
        printf("Enter ending address: ");
        scanf("%d",&s2);
        space->start = s1;
        space->end = s2;
        space->size = (s2-s1);
        space->status = 0;
        space->next = NULL;
        if(free_space ==NULL) free_space = space;
        else insert(free_space,space);
    }
    while(1){
        printf("Memory Allocation Algorithm\n");
        printf("1.First Fit\n");
        printf("2.Best Fit\n");
        printf("3.Worst Fit\n");
        printf("4.Exit\n");
        int ch;
        printf("Enter: ");
        scanf("%d",&ch);
        if(ch==4) break;
        while(1){
            printf("1.Entry/Allocate \n");
            printf("2.Exit/Deallocate \n");
            printf("3.Display\n");
            printf("4.Coalescing Holes\n");
            printf("5.Back to Algorithm\n");
            int c;
            printf("\nEnter your choice: ");
            scanf("%d",&c);
            if(c==5){
                if(ch==1) free(alloc1);
                if(ch==2) free(alloc2);
                if(ch==3) free(alloc3);
                NODE *vari = free_space;
                while(vari!=NULL){
                    if(vari->status!=0) vari->status = 0;
                    vari = vari->next;
                }
                break;
            }
            if(c==1){
                NODE *process = (NODE *)malloc(sizeof(NODE));
                int pid,size;
                printf("Enter process ID: ");
                scanf("%d",&pid);
                printf("Enter size: ");
                scanf("%d",&size);
                process->size = size;
                process->status = pid;
                process->next = NULL;
                if(ch==1){
                    NODE *temp = free_space;
                    while(temp!=NULL){
                        if(temp->size>=process->size && temp->status==0){
                            process->start = temp->start;
                            process->end = temp->end;
                            /*if(temp == free_space){
                                free_space = free_space->next;
                            }
                            else delete(free_space,temp);*/
                            temp->status = process->status;
                            printf("Hi\n");
                            if(alloc1==NULL) alloc1 = process;
                            else insert(alloc1,process);
                            break;
                        }
                        temp = temp->next;
                    }
                    printf("\n Free Pool\n");
                    display(free_space,'f');
                    printf("\n Allotted Memory\n");
                    display(alloc1,'t');
                    printf("\n Total Memory\n");
                    display(free_space,'t');
                    printf("\n");
                }
                if(ch==2){
                    NODE *temp = free_space;
                    int min;
                    int min_index;
                    int i=0;
                    while(temp!=NULL){
                        if(temp->status==0 && temp->size>=process->size){
                            min = temp->size;
                            min_index = i;
                            break;
                        }
                        i++;
                        temp = temp->next;
                    }
                    temp = free_space;
                    i=0;
                    while(temp!=NULL){
                        if(temp->size>=process->size && temp->size<min && temp->status == 0){
                            min = temp->size;
                            min_index = i;
                        }
                        i++;
                        temp = temp->next;
                    }
                    temp = free_space;
                    for(i=0;i<min_index;i++) temp = temp->next;
                    process->start = temp->start;
                    process->end = temp->end;
                    //if(temp == free_space) free_space = free_space->next;
                    //else delete(free_space,temp);
                    temp->status = process->status;
                    if(alloc2==NULL) alloc2 = process;
                    else insert(alloc2,process);
                    printf("\n Free Pool\n");
                    display(free_space,'f');
                    printf("\n Allotted Memory\n");
                    display(alloc2,'t');
                    printf("\n Total Memory\n");
                    display(free_space,'t');
                    printf("\n");
                }
                if(ch==3){
                    NODE *temp = free_space;
                    int max;
                    int max_index;
                    int i=0;
                    while(temp!=NULL){
                        if(temp->status==0 && temp->size>=process->size){
                            max = temp->size;
                            max_index = i;
                            break;
                        }
                        i++;
                        temp = temp->next;
                    }
                    temp = free_space;
                    i=0;
                    while(temp!=NULL){
                        if(temp->size>=process->size && temp->size>max && temp->status == 0){
                            max = temp->size;
                            max_index = i;
                        }
                        i++;
                        temp = temp->next;
                    }
                    temp = free_space;
                    for(i=0;i<max_index;i++) temp = temp->next;
                    process->start = temp->start;
                    process->end = temp->end;
                    //if(temp == free_space) free_space = free_space->next;
                    //else delete(free_space,temp);
                    temp->status = process->status;
                    if(alloc3==NULL) alloc3 = process;
                    else insert(alloc3,process);
                    printf("\n Free Pool\n");
                    display(free_space,'f');
                    printf("\n Allotted Memory\n");
                    display(alloc3,'t');
                    printf("\n Total Memory\n");
                    display(free_space,'t');
                    printf("\n");
                }
            }
            if(c==2){
                printf("Enter process ID: ");
                int n;
                scanf("%d",&n);
                if(ch==1){
                    NODE *temp = alloc1;
                    while(temp!=NULL){
                        if(temp->status == n){
                            /*NODE *data = (NODE *)malloc(sizeof(NODE));
                            data->status = 0;
                            data->start = alloc1->start;
                            data->end = alloc1->end;
                            data->size = data->end - data->start;
                            insert(free_space,data);
                            if(temp == alloc1) alloc1 = alloc1->next;
                            else delete(alloc1,temp);
                            break;*/
                            if(temp == alloc1) alloc1 = alloc1->next;
                            else delete(alloc1,temp);
                            break;
                        }
                        temp = temp->next;
                    }
                    temp = free_space;
                    while(temp!=NULL){
                        if(temp->status == n){
                            temp->status = 0;
                            printf("%d\n",temp->status);
                            break;
                        }
                        temp = temp->next;
                    }
                    printf("\n Free Pool\n");
                    display(free_space,'f');
                    printf("\n Allotted Memory\n");
                    display(alloc1,'t');
                    printf("\n Total Memory\n");
                    display(free_space,'t');
                    printf("\n");
                }
                if(ch==2){
                    NODE *temp = alloc2;
                    while(temp!=NULL){
                        if(temp->status == n){
                            /*NODE *data = (NODE *)malloc(sizeof(NODE));
                            data->status = 0;
                            data->start = alloc2->start;
                            data->end = alloc2->end;
                            data->size = data->end - data->start;
                            insert(free_space,data);
                            if(temp == alloc2) alloc1 = alloc2->next;
                            else delete(alloc2,temp);
                            break;*/
                            if(temp == alloc2) alloc2 = alloc2->next;
                            else delete(alloc2,temp);
                            break;
                        }
                        temp = temp->next;
                    }
                    temp = free_space;
                    while(temp!=NULL){
                        if(temp->status == n){
                            temp->status = 0;
                            break;
                        }
                        temp = temp->next;
                    }
                    printf("\n Free Pool\n");
                    display(free_space,'f');
                    printf("\n Allotted Memory\n");
                    display(alloc2,'t');
                    printf("\n Total Memory\n");
                    display(free_space,'t');
                    printf("\n");
                }
                if(ch==3){
                    NODE *temp = alloc3;
                    while(temp!=NULL){
                        if(temp->status == n){
                            /*NODE *data = (NODE *)malloc(sizeof(NODE));
                            data->status = 0;
                            data->start = alloc3->start;
                            data->end = alloc3->end;
                            data->size = data->end - data->start;
                            insert(free_space,data);
                            if(temp == alloc3) alloc1 = alloc1->next;
                            else delete(alloc3,temp);
                            break;*/
                            if(temp == alloc3) alloc3 = alloc3->next;
                            else delete(alloc3,temp);
                            break;
                        }
                        temp = temp->next;
                    }
                    temp = free_space;
                    while(temp!=NULL){
                        if(temp->status == n){
                            temp->status = 0;
                            break;
                        }
                        temp = temp->next;
                    }
                    printf("\n Free Pool\n");
                    display(free_space,'f');
                    printf("\n Allotted Memory\n");
                    display(alloc3,'t');
                    printf("\n Total Memory\n");
                    display(free_space,'t');
                    printf("\n");
                }
            }
            if(c==3){
                printf("\nFree Pool\n");
                display(free_space,'f');
                printf("\nAllocated Memory\n");
                if(ch==1) display(alloc1,'t');
                if(ch==2) display(alloc2,'t');
                if(ch==3) display(alloc3,'t');
                printf("\n Total Memory\n");
                display(free_space,'t');
                printf("\n");
            }
            if(c==4){
                NODE *temp = free_space;
                while(temp!=NULL){
                    if(temp->status==0){
                        if(temp->end == (temp->next)->start && (temp->next)->status==0){
                            NODE *temp1 = temp->next;
                            temp->next = temp1->next;
                            temp->end = temp1->end;
                            free(temp1);
                        }
                    }
                    temp = temp->next;
                }
            }
        }
        
    }
    
}
