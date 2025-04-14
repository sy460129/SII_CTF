#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#define MAX_CMD_ARG 10
#define BUFSIZE 256

char* cmdvector[MAX_CMD_ARG];
char  cmdline[BUFSIZ];
static struct sigaction sa;

void fatal(char *str){
    perror(str);
    exit(1);
}

int makelist(char *s, const char *delimiters, char** list, int MAX_LIST){	
  int i = 0;
  int numtokens = 0;
  char *snew = NULL;

  if( (s==NULL) || (delimiters==NULL) ) return -1;

  snew = s + strspn(s, delimiters);	/* Skip delimiters */
  if( (list[numtokens]=strtok(snew, delimiters)) == NULL )
    return numtokens;

  numtokens = 1;
  
  while(1){
     if( (list[numtokens]=strtok(NULL, delimiters)) == NULL)
    break;
     if(numtokens == (MAX_LIST-1)) return -1;
     numtokens++;
  }
  return numtokens;
}

void handle_sigchild(int signo){
  int status;
  pid_t pid;
  while((pid = waitpid(-1, &status, WNOHANG)) > 0){
    printf("\n[%d]\t Done\n", pid);
  }
}

void signal_ignore(int signo){
  printf("\t Ignore\n");
  strcpy(cmdline, "\n");
  fflush(stdout);
}
void init(){
  setvbuf(stdin, 0, 0, 0);
  setvbuf(stdout, 0, 0, 0);
}
int main(int argc, char**argv){
  int i=0;
  pid_t pid;
  signal(SIGCHLD, handle_sigchild);
  sa.sa_handler = signal_ignore;

  sigaction(SIGINT, &sa, NULL);
  sigaction(SIGQUIT, &sa, NULL);
  sigaction(SIGTSTP, &sa, NULL);
  
  while (1) {
    printf("> ");
    fflush(stdout);
    fgets(cmdline, BUFSIZ, stdin);    // read commands from terminal
    
    if(!strcmp(cmdline, "\n")) continue;
        
    cmdline[strlen(cmdline) -1] = '\0'; // replace '\n' with null character '\0'
 
    int tokens = makelist(cmdline, " \t", cmdvector, MAX_CMD_ARG);
    if (strstr(cmdline, "sh") != NULL) {
        printf("No hack\n");
        exit(0);
    }
    if(!strcmp(cmdvector[0], "exit")){
        printf("Shell Terminated...\n");
        exit(0);
    }
      
    else if(!strcmp(cmdvector[0], "cd")){
        if(chdir(cmdvector[1]) == -1){
            fatal("main() - chdir()");
        }
    }
    
    else if(!strcmp(cmdvector[0], "cat")){
        if(chdir(cmdvector[1]) == -1){
            printf("Do not use cat!!!\n");
        }
    }
    else if(!strcmp(cmdvector[0], "less")){
        if(chdir(cmdvector[1]) == -1){    
            printf("Do not use less!!!\n");
        }
    }
    else {       
        if(!strcmp(cmdvector[0], "ll")){
            cmdvector[0] = "ls";
            cmdvector[tokens] = "-als";
        }
        
        for(int i = 0; i < 26; i++){
             if(cmdvector[0][0] == i+'a'){
                  printf("Hmm...\n");
                  exit(1);
             }
        }
        
        int background = 0;
        if(!strcmp(cmdvector[tokens-1], "&")){
            cmdvector[tokens-1] = NULL;
            background = 1;
        }
        
        switch(pid=fork()){
            case 0:
                signal(SIGINT, SIG_DFL);
                signal(SIGQUIT, SIG_DFL);
                signal(SIGTSTP, SIG_DFL);
                execvp(cmdvector[0], cmdvector);
                fatal("main()");
            case -1:
                fatal("main()");
            default:
                if(background == 0){
                    wait(NULL);
                }
        }
    }
  }
  return 0;
}
