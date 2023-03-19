#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
 
int input_size = 5000;
 
void first(int fd[2], char* file){
    char buffer[input_size];
    int input = open(file, O_RDONLY);
    int num = read(input, buffer, input_size);
 
    char size[10];
    sprintf(size, "%d", num);
    write(fd[1], size, 10);
    write(fd[1], buffer, num);
}
 
void second(int fd1[2], int fd2[2], int l, int r) {
    char size[10];
    read(fd1[0], size, 10);
    int num;
    sscanf(size, "%d", &num);
 
    char buffer[num];
    read(fd1[0], buffer, num);

    int max = (l + r) / 2;
 
    for (int i = 0; i < max; ++i) {
        char cur = buffer[i + l];
        buffer[i + l] = buffer[r - i];
        buffer[r - i] = cur;
    }

    write(fd2[1], size, 10);
    write(fd2[1], buffer, num);
}
 
void third(int fd[2], char* file) {
    char size[10];
    read(fd[0], size, 10);
    int num;
    sscanf(size, "%d", &num);

    char buffer[num];
    read(fd[0], buffer, num);
 
    int output = open(file, O_WRONLY | O_CREAT, 0666);
    write(output, buffer, num);
}
 
int main(int argc, char **argv) {
    int input[2], output[2];
    pipe(input);
    pipe(output);
    
    int id = fork();
    if (id == 0) {
        first(input, argv[1]);
    } else {
        id = fork();
        if (id == 0) {
            int l = atoi(argv[3]);
            int r = atoi(argv[4]);
            second(input, output, l, r);
        }
        else {
            id = fork();
            if (id == 0) {
                third(output, argv[2]);
            }
        }
    }
    return 0;
}