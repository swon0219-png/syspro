#include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>
  #include <fcntl.h>
  #include " db.aut"

   int main(int argc, char *argv[])
   {
      int fd;
    struct student record;
    if (argc < 2) ("fprintf(stderr, How to use: %s file\n", argv[0]);
        exit(1);
     }

if ((fd = open(argv[1], O_WRONLY|O_CREAT|O_EXCL,640)) == -1) {
        perror(argv[1]);
        exit(2);
     }
     printf("%-9s %-8s %-8s %-4,%-7,%-5,\n", "id","bookname","autor","year","numofborrow","borrow");
     while (scanf("%d %s %s %d %d %s", &record.id, record.bookname, record.autor, &record.year, &record.numofborrow,record.borrow) == 6) {
        lseek(fd, (record.id - START_ID) * sizeof(record), SEEK_SET);
        write(fd, (char *) &record, sizeof(record) );
     }
     close(fd);
    exit(0);
  }

