#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    int c, line_number = 1;
    int start_arg = 1, show_line_number = 0;

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        show_line_number = 1;
        start_arg = 2;
    }

    if (argc <= start_arg) {
        fp = stdin;
        if (show_line_number) printf("%d ", line_number++);
        while ((c = getc(fp)) != EOF) {
            putc(c, stdout);
            if (show_line_number && c == '\n') printf("%d ", line_number++);
        }
        return 0;
    }

    for (int i = start_arg; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (!fp) {
            fprintf(stderr, "Error: Cannot open file %s\n", argv[i]);
            continue;
        }
        if (show_line_number) printf("%d ", line_number++);
        while ((c = getc(fp)) != EOF) {
            putc(c, stdout);
            if (show_line_number && c == '\n') printf("%d ", line_number++);
        }
        fclose(fp);
    }

    return 0;
}

