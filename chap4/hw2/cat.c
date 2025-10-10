#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 80

int main(int argc, char *argv[])
{
    FILE *fp;
    char buffer[MAXLINE];
    int line_number = 1;
    int start = 1;

    if (argc >= 2 && argv[1][0] == '-' && argv[1][1] == 'n')
        start = 2;

    if (argc <= start) {
        while (fgets(buffer, MAXLINE, stdin)) {
            if (argc >= 2 && argv[1][0] == '-' && argv[1][1] == 'n')
                printf("%3d %s", line_number++, buffer);
            else
                printf("%s", buffer);
        }
    } else {
        for (int i = start; i < argc; i++) {
            fp = fopen(argv[i], "r");
            if (!fp)
                continue;

            while (fgets(buffer, MAXLINE, fp)) {
                if (argc >= 2 && argv[1][0] == '-' && argv[1][1] == 'n')
                    printf("%3d %s", line_number++, buffer);
                else
                    printf("%s", buffer);
            }

            fclose(fp);
        }
    }

    return 0;
}

