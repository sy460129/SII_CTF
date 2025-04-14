#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
char buffer[64];
void init(){
    setvbuf(stdin, 0, _IONBF, 0);
    setvbuf(stdout, 0, _IONBF, 0);
}
int main(){
    init();
    srand(time(0));
    int s, x;
    x = rand() % 0x46464646;
    printf("Input: ");
    scanf("%s", &s);
    if((x ^ s) != 0x46){
        printf("result: 0x%x is not 0x46!\n", (x ^ s));
        return 0;
    }
    int fd = open("./flag.txt", O_RDONLY);
    if(fd == -1){
        perror("Failed to open file!");
        return 1;
    }
    ssize_t rd_size = read(fd, buffer, sizeof(buffer) - 1);
    if(rd_size == -1){
        perror("Failed to read file!");
        return 1;
    }
    printf("Flag: %s\n", buffer);
    close(fd);
}
