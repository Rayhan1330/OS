#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
void main(int argc,char * argv[])
{
    DIR *input_dir;int c=0;
    struct dirent *content=NULL;
    char str[50][50];
    if(argc<2){
        input_dir=opendir(".");
    }
    else{
        if(strcmp(argv[1],"-R")==0){
           input_dir=(argc>2)?opendir(argv[2]):opendir(".");
        }
        else{
            input_dir=opendir(argv[1]);
        }

    }
    if(input_dir==NULL){
        printf("error");
        exit(EXIT_FAILURE);
    }
    if(argc>=2 && strcmp(argv[1],"-R")==0){
        while((content=readdir(input_dir))!=NULL){
                strcpy(str[c++],content->d_name);
        }
        for(int i=0;i<c;i++){
            printf("%s\n",str[c-i-1]);
        }
    }
    else{
        while((content=readdir(input_dir))!=NULL){
            printf("%s\n",content->d_name);
        }
    }

    closedir(input_dir);
}

