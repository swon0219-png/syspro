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
    int fd, N, bookid;
    char c;
    struct book record;
	 if (argc < 2) {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        exit(1);
    }
	 if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror(argv[1]);
        exit(2);
    }
	 printf("--bookupdate--\n");

    do {
		  printf("0 bookId: borrow book, 1 bookId: return book > ");
        if (scanf("%d %d", &N, &bookid) != 2 || (N != 0 && N != 1)) {
            printf("Input Error\n");
            break;
        }
		  lseek(fd, (bookid - 1) * sizeof(record), SEEK_SET);
 if (read(fd, &record, sizeof(record)) <= 0 || record.id == 0) {
            printf("Record %d Null\n", bookid);
        } else {
			if (N == 0) { // borrow
                if (record.borrow == 1) {
                    printf("You cannot borrow below book since it has been borrowed:\n");
                    printf("%d  %s  %s  %s  %d  %s\n",
                           record.id, record.bookname, record.author, record.year,
                           record.numofborrow, "True");
					} else {
                    printf("You've got below book:\n");
                    printf("%d  %s  %s  %s  %d  %s\n",
                           record.id, record.bookname, record.author, record.year,
                           record.numofborrow, "False");

					record.borrow = 1;
                    record.numofborrow += 1;

                    lseek(fd, (bookid - 1) * sizeof(record), SEEK_SET);
                    write(fd, &record, sizeof(record));
                }
				  } else if (N == 1) { // return
                if (record.borrow == 0) {
                    printf("Book %d is not borrowed\n", bookid);
                } else {
                    record.borrow = 0;
					lseek(fd, (bookid - 1) * sizeof(record), SEEK_SET);
                    write(fd, &record, sizeof(record));

                    printf("You've returned below book:\n");
                    printf("%d  %s  %s  %s  %d  %s\n", 
                           record.id, record.bookname, record.author, record.year, 
                           record.numofborrow, "False");
                }
				}
        }

        printf("Continue? (Y/N) > ");
        scanf(" %c", &c);

    } while (c == 'Y' || c == 'y');

    close(fd);
    return 0;
}
