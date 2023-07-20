#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

#define STACK_EMPTY INT_MIN
struct Stack{
    unsigned int capacity; // Như n.
    int *arr; // Cơ bản là như mảng.
    int top; // Đỉnh stack, bắt đầu từ 0 tới n.
};

typedef struct Stack stack;

// Tạo 1 stack có FIXED-SIZE (Size cố định).
void *initStack(stack *S, unsigned int capacity)
{
    S->capacity = capacity;
    S->arr = (int *)malloc(S->capacity * sizeof(int));
    S->top = -1;
}

// Kiểm tra coi stack có đầy không.
bool isFull(stack STACK)
{
    return STACK.top == STACK.capacity - 1;
}

// Kiểm tra coi stack có rỗng không.
bool isEmpty(stack STACK)
{
    return STACK.top == -1;
}

// Đẩy dữ liệu vào stack.
void push(stack *STACK, int value)
{
    // Nếu đầy thì không push vào được thêm.
    if(isFull(*STACK)){
        printf("* Stack overflow!\n");
        printf("Exit code: %d\n", errno);
        exit(errno);
    }

    STACK->arr[++STACK->top] = value;
    printf("Pushed %d to Stack.\n", value);
}

int pop(stack *STACK)
{
    // Nếu rỗng thì không pop() được.
    if(isEmpty(*STACK)){
        printf("* Stack underflow!\n");
        printf("Exit code: %d\n", errno);
        exit(errno);
    }
    
    int popped = STACK->arr[STACK->top];
    printf("Popped %d.\n", popped);

    return STACK->arr[STACK->top--];
}

int peek(stack STACK)
{
    // Nếu rỗng thì không "Ngó" được.
    if(isEmpty(STACK)){
        printf("* Have nothing to peek in Stack!\n");
        return STACK_EMPTY;
    }
    return STACK.arr[STACK.top];
}

int main()
{
    stack s1;
    // Khởi tạo stack s1.
    initStack(&s1 ,10);

    push(&s1, 10);
    pop(&s1);
    printf("PEEK: %d.\n", peek(s1));

    return 0;
}