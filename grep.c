#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Insufficient arguments!!\n");
        exit(EXIT_FAILURE);
    }
    int fd = open(argv[2], O_RDONLY);
    if (fd == -1) {
        printf("Error in opening file!!");
        exit(EXIT_FAILURE);
    }
    int pattern_length = strlen(argv[1]);
    int line_number = 1;
    int count = 0;
    int n = 0, match = 0;
    char buffer[1000], j;
    while ((n = read(fd, buffer, sizeof(buffer))) > 0) {
        for (int i = 0; i < n; i++) {
            if (buffer[i] == '\n') {
                line_number++;
            }
            if (buffer[i] == argv[1][0]) {
                match = 1;
                for (j = 1; j < pattern_length; j++) {
                    if (buffer[i+j] != argv[1][j]) {
                        match = 0;
                        break;
                    }
                }
                if (match == 1) {
                    printf("Line %d: ", line_number);
                    for (j = i; j < n && buffer[j] != '\n'; j++) {
                        printf("%c", buffer[j]);
                    }
                    printf("\n");
                    count++;
                    i += pattern_length - 1;  // advance buffer index
                }
            }
        }
    }
    printf("The pattern %s occurred %d times in the file\n", argv[1], count);
    close(fd);
    exit(EXIT_SUCCESS);
    return 0;
}

