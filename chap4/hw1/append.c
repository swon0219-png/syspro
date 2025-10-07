#include <stdio.h>
int main(int argc, char *argv[])
{
    FILE *fp1, *fp2;
    char c;

    if (argc != 3) {
        fprintf(stderr, "%s file1 file2\n", argv[0]);
        return 1;
    }
    fp1 = fopen(argv[1], "r");
    if (fp1 == NULL) {
        fprintf(stderr, "%s\n", argv[1]); 
        return 2;
    }
    fp2 = fopen(argv[2], "a");
    if (fp2 == NULL) {
        fprintf(stderr, "%s\n", argv[2]);
        fclose(fp1);
        return 3;
    }
    while ((c = fgetc(fp1)) != EOF) {
        if (c != '\n' && c != '\r') 
            fputc(c, fp2);
    }

    fclose(fp1);
    fclose(fp2);

    printf("%s%s\n", argv[1], argv[2]);
    return 0;
}

