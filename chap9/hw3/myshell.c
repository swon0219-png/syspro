#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_CMD 1024
#define MAX_ARG 100

// 공백 기준으로 문자열 토큰화
void parse_command(char *cmd, char **argv) {
    int i = 0;
    argv[i] = strtok(cmd, " \t\n");
    while(argv[i] != NULL) {
        i++;
        argv[i] = strtok(NULL, " \t\n");
    }
}

// 명령어 실행
void execute_command(char *cmd) {
    char *argv[MAX_ARG];
    int background = 0;
    char *infile = NULL;
    char *outfile = NULL;

    // 백그라운드 확인
    char *amp = strchr(cmd, '&');
    if(amp) {
        background = 1;
        *amp = 0; // & 제거
    }

    // 입출력 리디렉션 확인
    char *out = strchr(cmd, '>');
    if(out) {
        *out = 0;
        outfile = strtok(out + 1, " \t\n");
    }
    char *in = strchr(cmd, '<');
    if(in) {
        *in = 0;
        infile = strtok(in + 1, " \t\n");
    }

    parse_command(cmd, argv);
    if(argv[0] == NULL) return; // 빈 명령어

    pid_t pid = fork();
    if(pid < 0) {
        perror("fork 실패");
        return;
    } else if(pid == 0) { // 자식 프로세스
        // 입력 리디렉션
        if(infile) {
            int fd = open(infile, O_RDONLY);
            if(fd < 0) { perror("입력 파일 열기 실패"); exit(1); }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        // 출력 리디렉션
        if(outfile) {
            int fd = open(outfile, O_WRONLY|O_CREAT|O_TRUNC, 0644);
            if(fd < 0) { perror("출력 파일 열기 실패"); exit(1); }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        execvp(argv[0], argv);
        perror("명령 실행 실패");
        exit(127);
    } else { // 부모 프로세스
        if(!background)
            waitpid(pid, NULL, 0); // 순차 실행
    }
}

int main() {
    char line[MAX_CMD];

    while(1) {
        printf("[shell] ");
        if(fgets(line, sizeof(line), stdin) == NULL) break;

        // 명령어 순차 실행(;) 분리
        char *cmd = strtok(line, ";");
        while(cmd != NULL) {
            execute_command(cmd);
            cmd = strtok(NULL, ";");
        }
    }
    printf("쉘 종료\n");
    return 0;
}

