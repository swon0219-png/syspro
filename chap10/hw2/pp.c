#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node **head, struct node **tail, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;
    if (*tail == NULL) {
        *head = *tail = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

int delete(struct node **head, struct node **tail) {
    if (*head == NULL) return -1;
    struct node *temp = *head;
    int val = temp->data;
    *head = (*head)->next;
    if (*head == NULL) *tail = NULL;
    free(temp);
    return val;
}

void printQueue(struct node *head) {
    printf("Print queue\n");
    while (head != NULL) {
        printf("%d\n", head->data);
        head = head->next;
    }
}

int main() {
    struct node *head = NULL;
    struct node *tail = NULL;
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
            addq(&head, &tail, num);
        }

        if (input[i] != '\0') {
            printQueue(head);
            return 0;
        }
    }

    return 0;
}

