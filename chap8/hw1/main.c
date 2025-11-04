#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

extern char **environ;

void print_env(char *env_name) {
    if (env_name == NULL) {
        for (char **env = environ; *env != NULL; env++) {
            printf("%s\n", *env);
        }
    } else {
        char *value = getenv(env_name);
        if (value != NULL)
            printf("%s=%s\n", env_name, value);
        else
            printf("Environment variable '%s' not found.\n", env_name);
    }
}

void print_help(char *progname) {
    printf("Usage: %s [option]\n", progname);
    printf("Options:\n");
    printf("  -e [VAR_NAME] : Print environment variable value (print all if no name given)\n");
    printf("  -u : Print user IDs with usernames\n");
    printf("  -g : Print group IDs with group names\n");
    printf("  -i : Print process ID\n");
    printf("  -p : Print parent process ID\n");
    printf("  -h : Show this help message\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_help(argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-e", 2) == 0) {
            if (strlen(argv[i]) > 2) {
                char *env_name = argv[i] + 2;
                print_env(env_name);
            }
            else if (i + 1 < argc && argv[i + 1][0] != '-') {
                print_env(argv[i + 1]);
                i++;
            } else {
                print_env(NULL);
            }
        }
        else if (strcmp(argv[i], "-u") == 0) {
            printf("Real UID: %d, Effective UID: %d\n", getuid(), geteuid());
        }
        else if (strcmp(argv[i], "-g") == 0) {
            printf("Real GID: %d, Effective GID: %d\n", getgid(), getegid());
        }
        else if (strcmp(argv[i], "-i") == 0) {
            printf("Process ID: %d\n", getpid());
        }
        else if (strcmp(argv[i], "-p") == 0) {
            printf("Parent Process ID: %d\n", getppid());
        }
        else if (strcmp(argv[i], "-h") == 0) {
            print_help(argv[0]);
        }
        else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
        }
    }

    return 0;
}

