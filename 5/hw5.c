#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
 
int input_size = 5000;
 
void first(char* name, char* file) { 
    int fd = open(name, O_WRONLY);
    char buffer[input_size];
    int input = open(file, O_RDONLY);
    int num = read(input, buffer, input_size);
 
    char size[10];
    sprintf(size, "%d", num);
    write(fd, size, 10);
    write(fd, buffer, num);
}
 
void second(char* name1, char* name2, int l, int r) {
    int fd1 = open(name1, O_RDONLY);
    int fd2 = open(name2, O_WRONLY);
    char size[10];
    read(fd1, size, 10);
    int num;
    sscanf(size, "%d", &num);
 
    char buffer[num];
    read(fd1, buffer, num);

    int max = (l + r) / 2;
 
    for (int i = 0; i < max; ++i) {
        char cur = buffer[i + l];
        buffer[i + l] = buffer[r - i];
        buffer[r - i] = cur;
    }

    write(fd2, size, 10);
    write(fd2, buffer, num);
}
 
void third(char* name, char* file) {
    int fd = open(name, O_RDONLY);
    char size[10];
    read(fd, size, 10);
    int num;
    sscanf(size, "%d", &num);

    char buffer[num];
    read(fd, buffer, num);
 
    int output = open(file, O_WRONLY | O_CREAT, 0666);
    write(output, buffer, num);
}
 
int main(int argc, char **argv) {
    char name1[] = "first.fifo";
    char name2[] = "second.fifo";

    (void)umask(0);

    mknod(name1, S_IFIFO | 0666, 0);
    mknod(name2, S_IFIFO | 0666, 0);
    
    int id = fork();
    if (id == 0) {
        first(name1, argv[1]);
    } else {
        id = fork();
        if (id == 0) {
            int l = atoi(argv[3]);
            int r = atoi(argv[4]);
            second(name1, name2, l, r);
        }
        else {
            id = fork();
            if (id == 0) {
                third(name2, argv[2]);
            }
        }
    }
    return 0;
}