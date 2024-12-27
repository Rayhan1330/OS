#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
int main(int argc, char* argv[])
{
    int fd1, fd2, n,a;
    char buff[1000],buff2[1000],ch;
    if(argc>=4 && strcmp(argv[1],"-i")==0){
        fd1=open(argv[2],O_RDONLY);
        fd2=open(argv[3],O_WRONLY);
    }
    else{
        fd1 = open(argv[1], O_RDONLY);
        fd2=open(argv[2],O_WRONLY);
    }
    if(fd1 == -1) {
        printf("Failed to open source file: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if(fd2 == -1) {
        printf("Failed to open destination file!\nCreating FILE\n");
        if(argc>=4){
            fd2=creat(argv[3],O_WRONLY);
        }
        else{
            fd2=creat(argv[2],O_WRONLY);
        }
    }
    while((n = read(fd1, buff, sizeof(buff))) > 0) {
        if(write(fd2, buff, n) != n && (a=read(fd2,buff2,1))==-1) {
            printf("Failed to write to destination file: %s\n", argv[2]);
            exit(EXIT_FAILURE);
        }
        else if(argc>=4 && strcmp(argv[1],"-i")==0){
            printf("Do you want to overwrite destination file ? (y/n)");
            if(scanf("%c",&ch)=='y'){
                if(write(fd2, buff, n) != n){
                    printf("Failed to write to destination file: %s\n", argv[2]);
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    if(n == -1) {
        printf("Failed to read source file: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if(close(fd1) != 0 || close(fd2) != 0) {
        printf("Failed to close files\n");
        exit(EXIT_FAILURE);
    }

    printf("File copied!\n");
    exit(EXIT_SUCCESS);
    return 0;
}

