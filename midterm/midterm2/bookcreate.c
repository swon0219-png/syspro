#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX 50
#define START_ID 1001001

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
    char input[10];

	    if (argc < 2) {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        exit(1);
    }

if ((fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0640)) == -1) {
        perror(argv[1]);
        exit(2);
    }

 while (scanf("%d %49s %49s %9s %d %9s",
                 &record.id,
                 record.bookname,
                 record.author,
				  record.year,
                 &record.numofborrow,
                 input) == 6) {

	   if (strcmp(input, "True") == 0 || strcmp(input, "true") == 0)
            record.borrow = 1;
        else
            record.borrow = 0;
		lseek(fd, (record.id - START_ID) * sizeof(record), SEEK_SET);
        write(fd, (char *)&record, sizeof(record));
    }
 close(fd);
    return 0;
}
