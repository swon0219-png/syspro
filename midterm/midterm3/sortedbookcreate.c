#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX 50

struct book {
    int id;
    char bookname[MAX];
    char author[MAX];
    char year[10];
    int numofborrow;
    int borrow;
};

struct node {
    struct book data;
    struct node *next;
};

void insert_sorted(struct node **head, struct book newbook) {
    struct node *newnode = malloc(sizeof(struct node));
    struct node *cur = *head;
    newnode->data = newbook;
    newnode->next = NULL;

    if (*head == NULL ||
        atoi(newbook.year) > atoi(cur->data.year) ||
        (atoi(newbook.year) == atoi(cur->data.year) && newbook.id > cur->data.id)) {
        newnode->next = *head;
        *head = newnode;
        return;
    }

    while (cur->next &&
          (atoi(cur->next->data.year) > atoi(newbook.year) ||
          (atoi(cur->next->data.year) == atoi(newbook.year) && cur->next->data.id > newbook.id))) {
        cur = cur->next;
    }

    newnode->next = cur->next;
    cur->next = newnode;
}

int main(int argc, char *argv[]) {
    if (argc < 2) exit(1);

    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) exit(2);

    struct node *head = NULL;
    struct book temp;
    char borrowstr[10];

    while (1) {
        if (scanf("%d %s %s %s %d %s",
                  &temp.id,
                  temp.bookname,
                  temp.author,
                  temp.year,
                  &temp.numofborrow,
                  borrowstr) != 6) break; // EOF 또는 잘못된 입력 시 종료

        if (strcmp(borrowstr, "True") == 0)
            temp.borrow = 1;
        else
            temp.borrow = 0;

        insert_sorted(&head, temp);
    }

    for (struct node *p = head; p; p = p->next)
        write(fd, &p->data, sizeof(p->data));

    close(fd);

    while (head) {
        struct node *tmp = head;
        head = head->next;
        free(tmp);
    }

    return 0;
}

