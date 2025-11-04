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
        if (strcmp(argv[i], "-e") == 0) {
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                print_env(argv[i + 1]);
                i++;
            } else {
                print_env(NULL);
            }
        } 
        else if (strcmp(argv[i], "-u") == 0) {
            uid_t real_uid = getuid();
            uid_t effective_uid = geteuid();
            struct passwd *real_pw = getpwuid(real_uid);
            struct passwd *eff_pw  = getpwuid(effective_uid);

            printf("My Realistic User ID : %d (%s)\n", 
                   real_uid, real_pw ? real_pw->pw_name : "unknown");
            printf("My Valid User ID : %d (%s)\n", 
                   effective_uid, eff_pw ? eff_pw->pw_name : "unknown");
        } 
        else if (strcmp(argv[i], "-g") == 0) {
            gid_t real_gid = getgid();
            gid_t effective_gid = getegid();
            struct group *real_gr = getgrgid(real_gid);
            struct group *eff_gr  = getgrgid(effective_gid);

            printf("My Realistic Group ID : %d (%s)\n",
                   real_gid, real_gr ? real_gr->gr_name : "unknown");
            printf("My Valid Group ID : %d (%s)\n",
                   effective_gid, eff_gr ? eff_gr->gr_name : "unknown");
        } 
        else if (strcmp(argv[i], "-i") == 0) {
            printf("my process number : [%d]\n", getpid());
        } 
        else if (strcmp(argv[i], "-p") == 0) {
            printf("my parent's process number : [%d]\n", getppid());
        } 
        else if (strcmp(argv[i], "-h") == 0) {
            print_help(argv[0]);
        } 
        else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            print_help(argv[0]);
        }
    }

    return 0;
}

