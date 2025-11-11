#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX 50

struct book {
    int id;
    char bookname[MAX];
    char author[MAX];
    char year[10];
    int numofborrow;
    int borrow;
};

int main(int argc, char *argv[]) {
    int fd;
    struct book record;
    char input[MAX];
    int found;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    while (1) {
        printf("input name of book > ");
        scanf("%s", input);

        // 종료 조건
        if (strcmp(input, "N") == 0 || strcmp(input, "n") == 0)
            break;

        lseek(fd, 0, SEEK_SET);
        found = 0;

        // 파일을 처음부터 끝까지 읽으며 비교
        while (read(fd, &record, sizeof(record)) > 0) {
            if (record.id == 0) continue;

            if (strcmp(record.bookname, input) == 0) {
                if (!found) {
                    printf("%-6s %-20s %-15s %-6s %-12s %-6s\n",
                           "id", "bookname", "author", "year", "numofborrow", "borrow");
                }
                printf("%-6d %-20s %-15s %-6s %-12d %-6s\n",
                       record.id,
                       record.bookname,
                       record.author,
                       record.year,
                       record.numofborrow,
                       record.borrow == 1 ? "True" : "False");
                found = 1;
            }
        }

        if (!found)
            printf("not found book name : '%s'\n", input);
    }

    close(fd);
    return 0;
}

