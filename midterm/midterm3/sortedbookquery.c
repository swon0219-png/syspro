#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX 50
#define MAXBOOK 1000  // 파일 내 최대 책 수 (필요시 조정)

struct book {
    int id;
    char bookname[MAX];
    char author[MAX];
    char year[10];
    int numofborrow;
    int borrow;
};

// numofborrow 기준 내림차순 정렬 함수
int compare(const void *a, const void *b) {
    struct book *bookA = (struct book *)a;
    struct book *bookB = (struct book *)b;
    return bookB->numofborrow - bookA->numofborrow; // 내림차순
}

int main(int argc, char *argv[]) {
    int fd;
    struct book record;
    struct book books[MAXBOOK];
    int count, N;
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

        // 파일 처음부터 읽기
        lseek(fd, 0, SEEK_SET);
        count = 0;

        // 모든 레코드 읽어서 배열에 저장
        while (read(fd, &record, sizeof(record)) > 0 && count < MAXBOOK) {
            if (record.id != 0) {
                books[count++] = record;
            }
        }

        // 내림차순 정렬
        qsort(books, count, sizeof(struct book), compare);

        // 출력 헤더
        printf("%-6s %-20s %-15s %-6s %-12s %-6s\n",
               "id", "bookname", "author", "year", "numofborrow", "borrow");

        // 필터링 및 출력
        for (int i = 0; i < count; i++) {
            if (N == 0 || (N == 1 && books[i].borrow == 1)) {
                printf("%-6d %-20s %-15s %-6s %-12d %-6s\n",
                       books[i].id,
                       books[i].bookname,
                       books[i].author,
                       books[i].year,
                       books[i].numofborrow,
                       books[i].borrow == 1 ? "True" : "False");
            }
        }

        printf("Continue? (Y/N) > ");
        scanf(" %c", &c);

        lseek(fd, 0, SEEK_SET);

    } while (c == 'Y' || c == 'y');

    close(fd);
    return 0;
}

