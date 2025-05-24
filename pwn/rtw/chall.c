#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
void init(){
    setvbuf(stdin, 0, 2, 0);
    setvbuf(stdout, 0, 2, 0);
    setvbuf(stderr, 0, 2, 0);
}
bool chance = false;

int main(){
    init();
    // for chall - one gadget
    // char msg[0x20];
    // char* buf[8];
    char msg[0x30];
    char* buf[6];
    if(!chance){        
        chance = true;
        printf("where are you?: ");
        read(0, &buf, 8);
        printf(&buf);
        printf("\n\n");
    
        printf("pardon?: ");
        read(0, &buf, 8);
        printf(&buf);
        printf("\n\n");
    }
    else{
        printf("wait.. you cannt return to main\n");
        exit(0);
    }

    printf("Leave final message: ");
    read(0, msg, 0x40);

    puts("Rejected...");
}