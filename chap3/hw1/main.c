#include <stdio.h>
#include <string.h>
#include "copy.h"

char lines[5][MAXLINE];
int lengths[5];

int main(){
    int i, j;
    char temp[MAXLINE];
    int temp_len;
    
    i = 0;
    while(i < 5) {
        fgets(lines[i], MAXLINE, stdin);
        
        int len = strlen(lines[i]);
        if(len > 0 && lines[i][len-1] == '\n') {
            lines[i][len-1] = '\0';
            len--;
        }
        lengths[i] = len;
        i++;
    }
    
    i = 0;
    while(i < 4) {
        j = 0;
        while(j < 4-i) {
            if(lengths[j] < lengths[j+1]) {
                temp_len = lengths[j];
                lengths[j] = lengths[j+1];
                lengths[j+1] = temp_len;
                
                copy(lines[j], temp);
                copy(lines[j+1], lines[j]);
                copy(temp, lines[j+1]);
            }
            j++;
        }
        i++;
    }
    
    i = 0;
    while(i < 5) {
        printf("%s\n", lines[i]);
        i++;
    }
    
    return 0;
}
