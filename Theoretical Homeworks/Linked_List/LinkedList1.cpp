#include <iostream>
#include <Windows.h>
void textcolor(int x) {
    HANDLE y = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(y, x);
}
// Khai báo cấu trúc NODE 
struct NODE {
    int data;
    struct NODE* next;
};
// Khai báo hai con trỏ đầu và cuối
struct LIST {
    NODE* head, * tail;
};
// Hàm để khởi tạo phần tử trong danh sách liên kết 
NODE* createNODE(int value) {
    NODE* pnode = new NODE;
    pnode->data = value;
    pnode->next = NULL;
    return pnode;
}
// Hàm để chèn một phần tử vào đầu danh sách liên kết
void insertHead(LIST* sl, int x) {
    NODE* pnode= createNODE(x);
    if (sl->head == NULL) {
        sl->head = sl->tail = pnode;
        return ;
    }
    pnode->next = sl->head;
    sl->head = pnode;
}
// Hàm để chèn một phần tử vào cuối danh sách liên kết
void insertTail(LIST* sl, int x) {
    NODE* pnode = createNODE(x);
    if (sl->head == NULL) {
        sl->head = sl->tail = pnode;
        return;
    }
    sl->tail->next = pnode;
    sl->tail = pnode;
}
// Hàm để chèn một phần tử vào vị trí bất kỳ trong danh sách liên kết 
void insertNODE(struct LIST* sl, int x, int pos) {
    if (pos < 1) {
        std::cout << "Vi tri chen khong hop le!\n";
        return;
    }
    if (pos == 1) {
        insertHead(sl, x);
        return;
    }
    NODE* previous_node = NULL, * current_node = sl->head;
    int i = 1;
    while (current_node != NULL && i < pos) {
        previous_node = current_node;
        current_node = current_node->next;
        i++;
    }
    if (i < pos) {
        std::cout << "Vi tri chen khong hop le!\n";
        return;
    }
    NODE* pnode = createNODE(x);
    if (previous_node == NULL) {
        sl->head = pnode;
    }
    else {
        previous_node->next = pnode;
    }
    pnode->next = current_node;
    if (current_node == NULL) {
        sl->tail = pnode;
    }
}
// Hàm để in các phần tử của danh sách liên kết 
void printList(LIST* sl) {
    if (sl->head == NULL) {
        std::cout << "LIST is empty\n";
        return;
    }
    NODE* pnode = sl->head;
    while (pnode != NULL) {
        std::cout << pnode->data << " ";
        pnode = pnode->next;
    }
}
// Hàm để xoá một phần tử trong danh sách liên kết
void deleteNode(LIST* sl, int x) {
    if (sl->head == NULL) {
        std::cout << "List is empty\n";
        return;
    }
    NODE* previous_node = NULL, * current_node = sl->head;
    while (current_node != NULL) {
        if (current_node->data == x) {
            if (previous_node == NULL) {
                sl->head = current_node->next;
                if (sl->head == NULL) {
                    sl->tail = NULL;
                }
            }
            else {
                previous_node->next = current_node->next;
                if (previous_node->next == NULL) {
                    sl->tail = previous_node;
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
int findmaxeven(LIST* l) {
    NODE* pnode = l->head;
    int max_even = -1;
    while (pnode != NULL) {
        if (pnode->data % 2 == 0 && pnode->data > max_even) {
            max_even = pnode->data;
        }
        pnode = pnode->next;
    }
    if (max_even == -1)
        return INT_MIN;
    return max_even;
}
int findmaxodd(LIST* sl) {
    NODE* pnode = sl->head;
    int max_odd = -1;
    while (pnode != NULL) {
        if (pnode->data%2!=0 && pnode->data > max_odd)
        {
            max_odd = pnode->data;
        }
        pnode = pnode->next;
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
        std::cout << "danh sach lien ket\n";
        LIST l;
        l.head = l.tail = NULL;
        std::cout << "nhap so luong NODE can tao: ";
        std::cin >> n;
        if (n==0)
            exit(0);
        textcolor(11);
        for (int i = 1; i <= n; i++)
        {
            std::cout << "NODE thu " << i << ": ";
            std::cin >> x;
            insertTail(&l, x);
        }
        std::cout << "danh sach lien ket: ";
        printList(&l);
        std::cout << "\n";

        textcolor(12);
        std::cout << "nhap phan tu can xoa: ";
        std::cin >> xdel;
        deleteNode(&l, xdel);
        std::cout << "danh sach lien ket sau khi xoa phan tu %d: ", xdel;
        printList(&l);
        std::cout << "\n";

        textcolor(14);
        std::cout << "nhap phan tu can chen va vi tri muon chen: ";
        std::cin >> y >> pos;
        insertNODE(&l, y, pos);
        printList(&l);
        std::cout << "\n";

        textcolor(9);
        int max_even = findmaxeven(&l);
        int max_odd = findmaxodd(&l);
        if (max_even != INT_MIN)
            std::cout << "so chan lon nhat trong danh sach lien ket: " << max_even << std::endl;
        else
            std::cout << "danh sach lien ket khong co so chan lon nhat.\n";
        if(max_odd!=INT_MIN)
            std::cout << "so le lon nhat trong danh sach lien ket: "<< max_odd << std::endl;
        else
            std::cout << "danh sach lien ket khong co so le lon nhat.\n";
        std::cout << "\n";
    }
    return 0;
}