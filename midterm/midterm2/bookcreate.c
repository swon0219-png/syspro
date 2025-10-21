#include <stdio.h>
  2   #include <stdlib.h>
  3   #include <unistd.h>
  4   #include <fcntl.h>
  5   #include " db.aut"
  6 
  7    int main(int argc, char *argv[])
  8    {
  9       int fd;
 10     struct student record;
 11     if (argc < 2) ("fprintf(stderr, How to use: %s file\n", argv[0]);
 12         exit(1);
 13      }
 14 
 15 if ((fd = open(argv[1], O_WRONLY|O_CREAT|O_EXCL,640)) == -1) {
 16         perror(argv[1]);
 17         exit(2);
 18      }
 19      printf("%-9s %-8s %-8s %-4,%-7,%-5,\n", "id","bookname","autor","year","numofborrow","borrow");
 20      while (scanf("%d %s %s %d %d %s", &record.id, record.bookname, record.autor, &record.year, &record.numofborrow,record.borrow) == 6) {
 21         lseek(fd, (record.id - START_ID) * sizeof(record), SEEK_SET);
 22         write(fd, (char *) &record, sizeof(record) );
 23      }
 24      close(fd);
 25     exit(0);
 26   }
