#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct file{
    char fname[20];
    struct file *next;
}file;

typedef struct dir{
    char name[20];
    file *files;
    struct dir *next;
    struct dir *dirs;
    struct dir *parent;
}dir;

void insert(dir *head,dir *sub){
    dir *temp = head;
    while(temp->next!=NULL) temp = temp->next;
    temp->next = sub;
}

void ins(file *head,file *sub){
    file *temp = head;
    while(temp->next!=NULL) temp = temp->next;
    temp->next = sub;
}

void display(dir *head){
    if(head!=NULL){
        printf("\nDirectory(s): \n");
        printf("Directory name: %s\n\n",head->name);
        file *temp = head->files;
        printf("Files: \n");
        while(temp!=NULL){
            printf("Filename: %s\n",temp->fname);
            temp = temp->next;
        }
        dir *temp1 = head->dirs;
        while(temp1!=NULL){
            display(temp1);
            temp1 = temp1->next;
        }
        
    }
}

int main(void){
    dir *head = NULL;
    dir *current = NULL;
    dir *new = (dir *)malloc(sizeof(dir));
    printf("Enter directory name: ");
    scanf("%s",new->name);
    new->files = NULL;
    new->dirs = NULL;
    new->parent = NULL;
    new->next = NULL;
    head = new;
    current = head;
    while(1){
        printf("1.Create\n");
        printf("2.Delete\n");
        printf("3.Display\n");
        printf("4.Go back to Previous Directory\n");
        printf("5.End\n");
        int c;
        scanf("%d",&c);
        if(c==1){
            printf("1.File\n");
            printf("2.Directory\n");
            int ch;
            scanf("%d",&ch);
            if(ch==1){
                file *new = (file *)malloc(sizeof(file));
                printf("Filename: ");
                scanf("%s",new->fname);
                new->next = NULL;
                if(current->files == NULL) current->files = new;
                else ins(current->files,new);
            }
            if(ch==2){
                dir *new1 = (dir *)malloc(sizeof(dir));
                printf("Enter directory name: ");
                scanf("%s",new1->name);
                new1->files = NULL;
                new1->dirs = NULL;
                new1->parent = current;
                if(current->dirs == NULL) current->dirs = new1;
                else insert(current->dirs,new1);
                current = new1;
            }
        }
        if(c==2){
            printf("1.File\n");
            printf("2.Directory\n");
            int ch;
            scanf("%d",&ch);
            printf("Enter name: ");
            char *name = (char *)malloc(sizeof(char)*20);
            scanf("%s",name);
            if(ch==1){
                file *temp = current->files;
                if(strcmp((current->files)->fname,name)==0){
                    current->files = (current->files)->next;
                    continue;
                }
                while(temp!=NULL){
                    file *temp1 = temp->next;
                    if(strcmp(temp1->fname,name)==0){
                        temp->next = temp1->next;
                        free(temp1);
                    }
                }
            }
            if(ch==2){
                dir *temp = current->dirs;
                if(strcmp((current->dirs)->name,name)==0){
                    current->dirs = (current->dirs)->next;
                    continue;
                }
                while(temp!=NULL){
                    dir *temp1 = temp->next;
                    if(strcmp(temp1->name,name)==0){
                        temp->next = temp1->next;
                        free(temp1);
                    }
                }
            }
        }
        if(c==3){
            display(current);
        }
        if(c==4){
            if(current->parent == NULL)
                printf("This is root directory\n");
            else
                current = current->parent;
        }
        if(c==5) break;
    }
}
