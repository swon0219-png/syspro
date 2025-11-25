#include <stdio.h>
#include <stdlib.h>

struct student {
    int id;
    char name[20];
};

int main()
{
    struct student *ptr;
    int n, i;

    printf("몇 명의 학생을 입력하겠습니까? ");
    scanf("%d", &n);  // ← 공백 제거

    if (n <= 0) {
        fprintf(stderr, "오류: 학생 수를 잘못 입력했습니다.\n");
        fprintf(stderr, "프로그램을 종료합니다.\n");
        return 1;
    }

    ptr = malloc(n * sizeof(struct student));  // ← 캐스팅 제거
    if (ptr == NULL) {
        perror("malloc");
        return 2;
    }

    printf("%d 명의 학번과 이름을 입력하세요.\n", n);
    for (i = 0; i < n; i++)
        scanf("%d %s", &ptr[i].id, ptr[i].name);

    printf("\n* 학생 정보(역순) *\n");
    for (i = n - 1; i >= 0; i--)
        printf("%d %s\n", ptr[i].id, ptr[i].name);

    free(ptr);  // ← 메모리 해제 필요
    return 0;
}

