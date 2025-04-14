#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/wait.h>

#define PORT 9738
// 오류 처리 함수
void fatal(char *str) {
    perror(str);
    exit(1);
}

int setup_server() {
    int server_fd;
    struct sockaddr_in server_addr;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        fatal("socket()");

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // 모든 IP에서 접근 허용
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        fatal("bind()");

    if (listen(server_fd, 5) < 0)
        fatal("listen()");

    return server_fd;
}

// myshell 실행
void run_shell(int client_fd) {
    dup2(client_fd, STDIN_FILENO);
    dup2(client_fd, STDOUT_FILENO);
    dup2(client_fd, STDERR_FILENO);
    close(client_fd);
    
    char *shell_argv[] = {"./myshell", NULL};
    execvp(shell_argv[0], shell_argv);
    fatal("execvp()");
}


int main() {
    int server_fd = setup_server();
    printf("Server is running on port %d\n", PORT);

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_fd;

        if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len)) < 0) {
            perror("accept()");
            continue;
        }

        printf("Connection accepted from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork()");
            close(client_fd);
            continue;
        }

        if (pid == 0) { 
            run_shell(client_fd);
            close(server_fd);
            exit(0);
        } else {
            close(client_fd); 
        }
    }

    close(server_fd);
    return 0;
}

