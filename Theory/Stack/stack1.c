#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100 // giới hạn kích thước của stack

// khai báo cấu trúc
struct Stack {
    int top;
    int data[MAX_SIZE];
} st;
// hàm kiểm tra xem stack có đầy hay không
int isFull() {
    if (st.top == MAX_SIZE - 1)
        return 1;
    else
        return 0;
}
// hàm kiểm tra xem stack có rỗng hay không
int isEmpty() {
    if (st.top == -1)
        return 1;
    else
        return 0;
}
// hàm đẩy (push) một phần tử vào stack
void push(int num) {
    if (isFull())
        printf("\nStack day.");
    else {
        st.top++;
        st.data[st.top] = num;
    }
}
// hàm lấy (pop) một phần tử ra khỏi stack
int pop() {
    int n;
    if (isEmpty()) 
    {
        printf("\nStack rỗng.");
        return (st.top);
    }
    else 
    {
        n = st.data[st.top];
        printf("\nPhần tử đã trích xuất: %d", st.data[st.top]);
        st.top--;
    }
    return(n);
}

// hàm hiển thị các phần tử trong stack
void display() {
    int i;
    if (isEmpty())
        printf("\nStack rong.");
    else {
        printf("\nCac phan tu trong stack la:\n");
        for (i = st.top; i >= 0; i--)
            printf("%d\n", st.data[i]);
    }
}

// chương trình của hàm main
int main() {
    int choose, num;
    st.top = -1;

    while (1) {
        printf("\nChon mot lua chon:");
        printf("\n1. Them phan tu vao stack.");
        printf("\n2. Lay phan tu ra khoi stack.");
        printf("\n3. Hien thi cac phan tu trong stack.");
        printf("\n4. Thoat chuong trinh.");

        scanf_s("%d", &choose);

        switch (choose) {
        case 1:
            printf("\nNhap mot so nguyen: ");
            scanf_s("%d", &num);
            push(num);
            break;
        case 2:
            pop();
            break;
        case 3:
            display();
            break;
        case 4:
            printf("\nChuong trinh ket thuc.\n");
            exit(0);
        default:
            printf("\nLua chon khong hop le. Vui long chon lai.\n");
        }
    }
    return 0;
}
