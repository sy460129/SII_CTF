#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void vuln(){
    system("/bin/sh");
}

void init(){
  setvbuf(stdin, 0, _IONBF, 0);
  setvbuf(stdout, 0, _IONBF, 0);
}

int main(){
  init();
  char* key[7];
  void* tmp = malloc(8);
  FILE* rand;
  rand = fopen("/dev/urandom", "r");
  fread(tmp, 7, 1, rand);
  fclose(rand);
  printf("Verify Admin\n");
  while(1){
    printf("key: ");
    scanf("%8s", &key);
    if(strncmp((const char*)tmp, key, 7)){
      printf(key);
      printf(" is wrong..\n");
    }
    else {
      printf("You are Admin! But..\n");
      break;
    }
  }
  printf("The key was exposed...\n");
  printf("You should change the key\n");
  free(tmp);
  printf("key: ");
  read(0, key, 72);
  printf("Your input: ");
  printf(key);

  puts("Good\n");
}
