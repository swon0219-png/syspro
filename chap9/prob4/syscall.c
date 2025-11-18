#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>

int mysystem (const char *cmdstring) {
    int pid, status;

    if (cmdstring == NULL)
        return 1;

    pid = fork();
    if (pid == -1)
        return -1;

    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
        _exit(127);
    }

    do {
        if (waitpid(pid, &status, 0) == -1) {
            if (errno != EINTR)
                return -1;
        } else {
            return status;
        }
    } while (1);
}

int main()
{
    int status;

    /* 1. mysystem()으로 date */
    if ((status = mysystem("date")) < 0)
        perror("mysystem() 오류");
    else
        printf("end code %d\n", WEXITSTATUS(status));

    /* 2. mysystem()으로 hello (없는 명령어) */
    if ((status = mysystem("hello")) < 0)
        perror("mysystem() 오류");
    else
        printf("end code %d\n", WEXITSTATUS(status));

    /* 3. 반드시 system() 함수 사용 — who; exit 44 */
    status = mysystem("who; exit 44");
    if (status < 0)
        perror("system() 오류");
    else
        printf("end code %d\n", WEXITSTATUS(status));

    return 0;
}

