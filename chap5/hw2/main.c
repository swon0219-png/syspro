#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

typedef struct {
    char *content;
    int length;
} TextLine;

TextLine* allocateLines(int count) {
    TextLine *array = (TextLine*)malloc(sizeof(TextLine) * count);
    int i = 0;
    while (i < count) {
        array[i].content = (char*)malloc(256);
        array[i].length = 0;
        i++;
    }
    return array;
}

void freeLines(TextLine *array, int count) {
    int i = 0;
    while (i < count) {
        free(array[i].content);
        i++;
    }
    free(array);
}

int parseFile(TextLine *storage, const char *filename) {
    int descriptor = open(filename, O_RDONLY);
    if (descriptor < 0) return -1;
    
    char ch;
    int currentLine = 0;
    int position = 0;
    
    while (read(descriptor, &ch, sizeof(char)) > 0) {
        if (ch != '\n') {
            storage[currentLine].content[position++] = ch;
        } else {
            storage[currentLine].content[position] = '\0';
            storage[currentLine].length = position;
            currentLine++;
            position = 0;
        }
    }
    
    if (position != 0) {
        storage[currentLine].content[position] = '\0';
        storage[currentLine].length = position;
        currentLine++;
    }
    
    close(descriptor);
    return currentLine;
}

void reverseWrite(const char *filename, TextLine *data, int count) {
    int descriptor = open(filename, O_WRONLY | O_TRUNC);
    if (descriptor < 0) return;
    
    int current = count;
    while (current > 0) {
        current--;
        int idx = 0;
        while (idx < data[current].length) {
            write(descriptor, &data[current].content[idx], sizeof(char));
            idx++;
        }
        if (current >= 0) {
            char newline = '\n';
            write(descriptor, &newline, sizeof(char));
        }
    }
    
    close(descriptor);
}

int main(void) {
    const char *filepath = "test.txt";
    TextLine *buffer = allocateLines(100);
    
    int totalLines = parseFile(buffer, filepath);
    
    if (totalLines > 0) {
        reverseWrite(filepath, buffer, totalLines);
    }
    
    freeLines(buffer, 100);
    
    return 0;
}
