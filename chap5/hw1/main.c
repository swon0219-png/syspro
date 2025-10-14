#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_LINES 100
#define MAX_COLS 256

int readFile(char savedText[][MAX_COLS]) {
    int fd;
    char buf;
    int line = 0;
    int col = 0;

    fd = open("test.txt", O_RDONLY);
    if (fd == -1) return -1;

    while (read(fd, &buf, 1) > 0) {
        if (buf == '\n') {
            savedText[line][col] = '\0';
            line++;
            col = 0;
        } else {
            savedText[line][col] = buf;
            col++;
        }
    }

    if (col > 0) {
        savedText[line][col] = '\0';
        line++;
    }

    close(fd);
    return line;
}

void printOneLine(char savedText[][MAX_COLS], int n, int total) {
    if (n < 1 || n > total) return;
    printf("%s\n", savedText[n-1]);
}

void printRange(char savedText[][MAX_COLS], int start, int end, int total) {
    int i;
    if (start < 1) start = 1;
    if (end > total) end = total;
    for (i = start; i <= end; i++) {
        printf("%s\n", savedText[i-1]);
    }
}

void printAll(char savedText[][MAX_COLS], int total) {
    int i;
    for (i = 0; i < total; i++) {
        printf("%s\n", savedText[i]);
    }
}

void printList(char savedText[][MAX_COLS], char *input, int total) {
    char *token;
    int num;
    token = strtok(input, ",");
    while (token != NULL) {
        num = atoi(token);
        printOneLine(savedText, num, total);
        token = strtok(NULL, ",");
    }
}

void processInput(char savedText[][MAX_COLS], char *input, int total) {
    char temp[256];
    int start, end;
    if (strcmp(input, "*") == 0) {
        printAll(savedText, total);
        return;
    }
    if (strchr(input, '-') != NULL) {
        if (sscanf(input, "%d-%d", &start, &end) == 2) {
            printRange(savedText, start, end, total);
            return;
        }
    }
    if (strchr(input, ',') != NULL) {
        strcpy(temp, input);
        printList(savedText, temp, total);
        return;
    }
    start = atoi(input);
    if (start > 0) {
        printOneLine(savedText, start, total);
    }
}

int main() {
    char savedText[MAX_LINES][MAX_COLS];
    char input[256];
    int totalLines;

    totalLines = readFile(savedText);
    if (totalLines == -1) return 1;

    printf("File read success\n");
    printf("Total Line : %d\n", totalLines);
    printf("You can choose 1 ~ %d Line\n", totalLines);
    printf("Pls 'Enter' the line to select : ");

    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0';
        if (strlen(input) > 0) {
            processInput(savedText, input, totalLines);
        }
    }

    return 0;
}

