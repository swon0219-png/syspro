#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    char c;
    FILE *fp1, *fp2;
    int mode;
    
    if (argc != 4) {
        fprintf(stderr, "How to use: %s mode source.txt destination.txt\n", argv[0]);
        return 1;
    }
    
    mode = atoi(argv[1]);
    
    if (mode < 0 || mode > 2) {
        fprintf(stderr, "Mode Error\n");
        return 1;
    }
    
    fp1 = fopen(argv[2], "r");
    if (fp1 == NULL) {
        fprintf(stderr, "File %s Open Error\n", argv[2]);
        return 2;
    }
    
    fp2 = fopen(argv[3], "w");
    if (fp2 == NULL) {
        fprintf(stderr, "File %s Open Error\n", argv[3]);
        fclose(fp1);
        return 2;
    }
    
    while ((c = fgetc(fp1)) != EOF) {
        if (mode == 1) {
            c = tolower(c);
        } else if (mode == 2) {
            c = toupper(c);
        }
        
        if (fputc(c, fp2) == EOF) {
            fprintf(stderr, "Write Error\n");
            fclose(fp1);
            fclose(fp2);
            return 3;
        }
    }
    
    fclose(fp1);
    fclose(fp2);
    return 0;
}

