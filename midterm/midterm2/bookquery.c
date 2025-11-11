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
    int N;
    char c;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    do {
        printf("--bookquery--\n");
        printf("0: list of all books, 1: list of available books > ");
        if (scanf("%d", &N) != 1 || (N != 0 && N != 1)) {
            printf("Input Error\n");
            break;
        }

        printf("%-6s %-20s %-15s %-6s %-12s %-6s\n",
               "id", "bookname", "author", "year", "numofborrow", "borrow");

        lseek(fd, 0, SEEK_SET);

        while (read(fd, &record, sizeof(record)) > 0) {
            if (record.id == 0) continue;

            if (N == 0 || (N == 1 && record.borrow == 1)) {
                printf("%-6d %-20s %-15s %-6s %-12d %-6s\n",
                       record.id,
                       record.bookname,
                       record.author,
                       record.year,
                       record.numofborrow,
                       record.borrow == 1 ? "True" : "False");
            }
        }

        printf("Continue? (Y/N) > ");
        scanf(" %c", &c);

        lseek(fd, 0, SEEK_SET);

    } while (c == 'Y' || c == 'y');

    close(fd);
    return 0;
}

