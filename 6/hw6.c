#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
 
int input_size = 5000;
sem_t sem;

 
void first(int fd[2], char* file, char* file2){
    sem_wait(&sem);
    char buffer[input_size];
    int input = open(file, O_RDONLY);
    int num = read(input, buffer, input_size);
 
    char size[10];
    sprintf(size, "%d", num);
    write(fd[1], size, 10);
    write(fd[1], buffer, num);

    sem_post(&sem);

    usleep(10);

    sem_wait(&sem);

    char res[num];
    read(fd[0], res, num);
 
    int output = open(file2, O_WRONLY | O_CREAT, 0666);
    write(output, res, num);
}
 
void second(int fd[2], int l, int r) {
    sem_wait(&sem);
    char size[10];
    read(fd[0], size, 10);
    int num;
    sscanf(size, "%d", &num);
 
    char buffer[num];
    read(fd[0], buffer, num);

    int max = (l + r) / 2;
 
    for (int i = 0; i < max; ++i) {
        char cur = buffer[i + l];
        buffer[i + l] = buffer[r - i];
        buffer[r - i] = cur;
    }

    write(fd[1], buffer, num);
    sem_post(&sem);
}
 
int main(int argc, char **argv) {
    int fd[2];
    sem_init(&sem, 0, 1);
    pipe(fd);
    
    int id1 = fork();
    if (id1 == 0) {
        first(fd, argv[1], argv[2]);
        exit(EXIT_SUCCESS);
    }
    int id2 = fork();
    if (id2 == 0) {
        int l = atoi(argv[3]);
        int r = atoi(argv[4]);
        second(fd, l, r);
        exit(EXIT_SUCCESS);
    }

    sem_destroy(&sem);

    return 0;
}