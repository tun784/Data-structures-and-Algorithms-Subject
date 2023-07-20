#include<stdio.h> 
#include<stdlib.h> 
#include <Windows.h>
textcolor(int x) {
    HANDLE y = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(y, x);
}
// Khai báo cấu trúc node 
typedef struct Node {
    int data;
    struct Node* next;
}Node;
// Khai báo hai con trỏ đầu và cuối
typedef struct List {
    Node* head, * tail;
}List;
// Hàm để khởi tạo phần tử trong danh sách liên kết 
Node* createNode(int x) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = x;
    node->next = NULL;
    return node;
}
// Hàm để chèn một phần tử vào đầu danh sách liên kết
void insertHead(List* list, int x) {
    Node* node = createNode(x);
    if (list->head == NULL) {
        list->head = list->tail = node;
        return ;
    }
    node->next = list->head;
    list->head = node;
}
// Hàm để chèn một phần tử vào cuối danh sách liên kết
void insertTail(List* list, int x) {
    Node* node = createNode(x);
    if (list->head == NULL) {
        list->head = list->tail = node;
        return;
    }
    list->tail->next = node;
    list->tail = node;
}
// Hàm để chèn một phần tử vào vị trí bất kỳ trong danh sách liên kết 
void insertNode(struct List* list, int x, int pos) {
    if (pos < 1) {
        printf("Vi tri chen khong hop le!\n");
        return;
    }
    if (pos == 1) {
        insertHead(list, x);
        return;
    }
    struct Node* previous_node = NULL, * current_node = list->head;
    int i = 1;
    while (current_node != NULL && i < pos) {
        previous_node = current_node;
        current_node = current_node->next;
        i++;
    }
    if (i < pos) {
        printf("Vi tri chen khong hop le!\n");
        return;
    }
    struct Node* node = createNode(x);
    if (previous_node == NULL) {
        list->head = node;
    }
    else {
        previous_node->next = node;
    }
    node->next = current_node;
    if (current_node == NULL) {
        list->tail = node;
    }
}
// Hàm để in các phần tử của danh sách liên kết 
void printList(List* list) {
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }
    Node* node = list->head;
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}
// Hàm để xoá một phần tử trong danh sách liên kết
void delete(List* list, int x) {
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }
    Node* previous_node = NULL, * current_node = list->head;
    while (current_node != NULL) {
        if (current_node->data == x) {
            if (previous_node == NULL) {
                list->head = current_node->next;
                if (list->head == NULL) {
                    list->tail = NULL;
                }
            }
            else {
                previous_node->next = current_node->next;
                if (previous_node->next == NULL) {
                    list->tail = previous_node;
                }
            }
            free(current_node);
            return;
        }
        previous_node = current_node;
        current_node = current_node->next;
    }
}
// Hàm để tìm số chẵn lớn nhất 
int findmaxeven(List* list) {
    Node* node = list->head;
    int max_even = -1;
    while (node != NULL) {
        if (node->data % 2 == 0 && node->data > max_even) {
            max_even = node->data;
        }
        node = node->next;
    }
    if (max_even == -1)
        return INT_MIN;
    return max_even;
}
int findmaxodd(List* list) {
    Node* node = list->head;
    int max_odd = -1;
    while (node != NULL) {
        if (node->data%2!=0 && node->data > max_odd)
        {
            max_odd = node->data;
        }
        node = node->next;
    }
    if (max_odd==-1)
        return INT_MIN;
    return max_odd;
}
// Hàm chính 
int main() {
    while (1) {
        int x, n, xdel,y,pos;
        textcolor(10);
        printf("danh sach lien ket\n");
        List list;
        list.head = list.tail = NULL;
        printf("nhap so luong node can tao: ");
        scanf_s("%d", &n);
        if (n==0)
            exit(0);
        textcolor(11);
        for (int i = 1; i <= n; i++)
        {
            printf("node thu %d: ", i);
            scanf_s("%d", &x);
            insertTail(&list, x);
        }
        printf("danh sach lien ket: ");
        printlist(&list);
        printf("\n");
        textcolor(12);
        printf("nhap phan tu can xoa: ");
        scanf_s("%d", &xdel);
        delete(&list, xdel);
        printf("danh sach lien ket sau khi xoa phan tu %d: ", xdel);
        printlist(&list);
        printf("\n");
        textcolor(14);
        printf("nhap phan tu can chen va vi tri muon chen: ");
        scanf_s("%d%d", &y, &pos);
        insertnode(&list, y,pos);
        printlist(&list);
        printf("\n");
        textcolor(9);
        int max_even = findmaxeven(&list);
        int max_odd = findmaxodd(&list);
        if (max_even != INT_MIN)
            printf("so chan lon nhat trong danh sach lien ket: %d\n", max_even);
        else
            printf("danh sach lien ket khong co so chan lon nhat.\n");
        if(max_odd!=INT_MIN)
            printf("so le lon nhat trong danh sach lien ket: %d\n", max_odd);
        else
            printf("danh sach lien ket khong co so le lon nhat.\n");
        printf("\n");
    }
    return 0;
}