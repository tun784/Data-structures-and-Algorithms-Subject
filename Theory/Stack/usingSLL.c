#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#define STACK_EMPTY INT_MIN

struct StackNode{
    int data;
    struct StackNode *link;
};

typedef struct StackNode SN;

// Kiểm tra Stack có rỗng hay không.
bool isEmpty(SN *top)
{
    return top == NULL;
}

// Tạo một Node cho stack.
SN *newNode(int value)
{
    SN *stackNode = (SN*)malloc(sizeof(SN));
    if(stackNode == NULL){
        printf("Failed to allocate memory.\n");
        exit(2);
    }
    stackNode->data = value;
    stackNode->link = NULL;
    return stackNode;
}

// Đẩy dữ liệu vào Stack theo chiều từ dưới lên.
// Do đó top sẽ thay đổi liên tục, nên ta phải dùng ** để sửa địa chỉ của top.
void push(SN **top, int value)
{
    SN *stackNode = newNode(value);
    stackNode->link = *top;
    *top = stackNode;
    printf("%d pushed to stack.\n", value);
}
// Lấy dữ liệu từ đỉnh stack, nên dữ liệu đó sẽ bị xoá sau khi lấy ra.
// Xoá từ đỉnh xuống, có nghĩa là xoá từ vị trí top trở đi; nên địa chỉ top sẽ thay đổi.
// Ta dùng ** để hỗ trợ thay đổi địa chỉ.
int pop(SN **top) {
    // Nếu rỗng thì không lấy được.
    if(isEmpty(*top))
        return STACK_EMPTY;

    SN *temp = *top;
    *top = (*top)->link;
    int popped = temp->data;
    free(temp);

    return popped;
}

// "Ngó" dữ liệu từ đỉnh stack.
int peek(SN* top)
{
    // Nếu rỗng thì không "Ngó" được.
    if (isEmpty(top))
        return INT_MIN;
    return top->data;
}

// In dữ liệu đang hiện hữu trong stack.
void present_element(SN *top)
{
    SN *temp = top;
    while(temp != NULL){
        printf("%d [%p]\n", temp->data, temp);
        temp = temp->link;
    }
}

int main()
{
    // Ta có thể coi top như head.
    SN *top = NULL;

    // Địa chỉ của con trỏ top: &top.
    printf("&top[%p]->top[%p]\n", &top, top);
    push(&top, 10); // Đẩy dữ liệu.
    printf("&top[%p]->top[%p]\n", &top, top);
    push(&top, 20); // Đẩy dữ liệu.
    printf("&top[%p]->top[%p]\n", &top, top);
    push(&top, 30); // Đẩy dữ liệu.
    printf("&top[%p]->top[%p]\n", &top, top);
    push(&top, 40); // Đẩy dữ liệu.
    printf("&top[%p]->top[%p]\n", &top, top);

    printf("-----------------\n");
    present_element(top); // Xuất dữ liệu.
    return 0;
}