#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node **top, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

int pop(struct node **top) {
    if (*top == NULL) return -1;
    struct node *temp = *top;
    int val = temp->data;
    *top = temp->next;
    free(temp);
    return val;
}

void printStack(struct node *top) {
    printf("Print  stack\n");
    while (top != NULL) {
        printf("%d\n", top->data);
        top = top->next;
    }
}

int main() {
    struct node *top = NULL;
    char input[100];

    while (scanf("%s", input) == 1) {
        int i = 0;
        int num = 0;
        int isNumber = 0;

        while (isdigit(input[i])) {
            num = num * 10 + (input[i] - '0');
            i++;
            isNumber = 1;
        }

        if (isNumber) {
            push(&top, num);
        }

        if (input[i] != '\0') {
            printStack(top);
            return 0;
        }
    }

    return 0;
}

