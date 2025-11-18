#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_CMD 1024
#define MAX_ARG 100

void parse_cmd(char *cmd, char **argv) {
    int i = 0;
    argv[i] = strtok(cmd, " \t\n");
    while(argv[i] != NULL) {
        i++;
        argv[i] = strtok(NULL, " \t\n");
    }
}

int main() {
    char line[MAX_CMD];
    char *argv[MAX_ARG];

    while(1) {
        printf("Pls input cmd : ");
        if(fgets(line, sizeof(line), stdin) == NULL) break;

        int background = 0;
        char *pos = strchr(line, '&');
        if(pos) {
            background = 1;
            *pos = 0;
        }

        parse_cmd(line, argv);
        if(argv[0] == NULL) continue;

        printf("[%d] Parent process start\n", getpid());

        pid_t pid = fork();
        if(pid < 0) {
            perror("fork 실패");
            continue;
        } else if(pid == 0) {
            if(background)
                printf("[%d] child process start\n", getpid());

            execvp(argv[0], argv);
            // execvp 실패 시
            if(!background) { 
                // 잘못된 명령어이면 Parent process end/Exit만 출력
                _exit(1); 
            }
        } else {
            int status;
            waitpid(pid, &status, 0);

            if(WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                printf("Parent process end\n");
                printf("Exit\n\n");
            } else {
                if(background)
                    printf("[%d] child process end %d\n", getpid(), pid);
                printf("SUCCESS\n\n");
            }
        }
    }
    return 0;
}

