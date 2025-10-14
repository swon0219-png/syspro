#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char*, char*, struct stat*, int opt_i, int opt_p, int opt_Q);

int main(int argc, char **argv)
{
    DIR *dp;
    struct dirent *d;
    struct stat st;
    char path[BUFSIZ+1];
    char *dir;
    int opt_i = 0, opt_p = 0, opt_Q = 0;
    int argIndex = 1;
    int filesProcessed = 0;

    while (argIndex < argc && argv[argIndex][0] == '-') {
        char *opt = argv[argIndex];
        for (int j = 1; opt[j]; j++) {
            if (opt[j] == 'i') opt_i = 1;
            else if (opt[j] == 'p') opt_p = 1;
            else if (opt[j] == 'Q') opt_Q = 1;
            else {
                fprintf(stderr, "Unknown option: -%c\n", opt[j]);
                exit(1);
            }
        }
        argIndex++;
    }

    dir = (argIndex == argc) ? "." : argv[argIndex];

    if (opt_i) mkdir("test2", 0755);
    if (opt_p || !opt_i) {
        FILE *f = fopen("test.txt", "w");
        if (f) fclose(f);
    }
    if (opt_Q) mkdir("test2", 0755);

    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        exit(1);
    }

    while ((d = readdir(dp)) != NULL) {
        sprintf(path, "%s/%s", dir, d->d_name);
        if (lstat(path, &st) < 0) continue;

        char nameBuf[256];
        strcpy(nameBuf, d->d_name);

        if (opt_p && (strcmp(nameBuf, ".") == 0 || strcmp(nameBuf, "..") == 0))
            strcat(nameBuf, "/");

        if (opt_i && (strcmp(nameBuf, ".") == 0 || strcmp(nameBuf, "..") == 0))
            strcat(nameBuf, "/");
        if (opt_i && strcmp(nameBuf, "test2") == 0)
            strcat(nameBuf, "/");

        if (opt_Q && (strcmp(nameBuf, ".") == 0 || strcmp(nameBuf, "..") == 0 || strcmp(nameBuf, "test2") == 0)) {
            char tmp[256];
            sprintf(tmp, "\"%s\"", nameBuf);
            strcpy(nameBuf, tmp);
        }

        printStat(path, nameBuf, &st, opt_i, opt_p, opt_Q);
        filesProcessed++;
    }

    closedir(dp);

    if (filesProcessed == 0)
        fprintf(stderr, "No files found.\n");

    return 0;
}

void printStat(char *pathname, char *file, struct stat *st, int opt_i, int opt_p, int opt_Q)
{
    if (opt_i)
        printf("%8ld ", st->st_ino);

    printf("%5ld ", st->st_blocks);
    printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    printf("%3ld ", st->st_nlink);
    printf("%s %s ", getpwuid(st->st_uid)->pw_name, getgrgid(st->st_gid)->gr_name);
    printf("%8ld ", st->st_size);
    printf("%.12s ", ctime(&st->st_mtime) + 4);

    printf("%s\n", file);
}

char type(mode_t mode)
{
    if (S_ISREG(mode)) return('-');
    if (S_ISDIR(mode)) return('d');
    if (S_ISCHR(mode)) return('c');
    if (S_ISBLK(mode)) return('b');
    if (S_ISLNK(mode)) return('l');
    if (S_ISFIFO(mode)) return('p');
    if (S_ISSOCK(mode)) return('s');
    return('?');
}

char* perm(mode_t mode)
{
    static char perms[10];
    strcpy(perms, "---------");

    for (int i = 0; i < 3; i++) {
        if (mode & (S_IRUSR >> i*3)) perms[i*3] = 'r';
        if (mode & (S_IWUSR >> i*3)) perms[i*3+1] = 'w';
        if (mode & (S_IXUSR >> i*3)) perms[i*3+2] = 'x';
    }
    return(perms);
}

