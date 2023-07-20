#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
textcolor(int x) {
	HANDLE y = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(y, x);
}
//Khởi tạo một node trong danh sách liên kết
typedef struct node {
	int data;
	struct NODE* next;
}NODE;
typedef struct list
{
	NODE* head;
	NODE* tail;
}LIST;
void headtail(LIST* l) {
	l->head = NULL;
	l->tail = NULL;
}
NODE* createNode(int data) { // hàm tạo node 
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

void insertHead(int data) { // hàm chèn đầu danh sách
	LIST l;
	NODE* newNode = createNode(data);

	if (l.head == NULL) {
		l.head = newNode;
		return;
	}

	newNode->next = l.head;
	l.head = newNode;
}

void insertTail(int data) { // hàm chèn cuối danh sách
	LIST l;
	NODE* newNode = createNode(data);

	if (l.tail == NULL) {
		l.tail = newNode;
		return;
	}

	NODE* currentNode = l.tail;
	while (currentNode->next != NULL) {
		currentNode = currentNode->next;
	}
	currentNode->next = newNode;
}

void printList() { // hàm xuất dữ liệu danh sách
	LIST l;
	NODE* currentNode = l.head;
	if (currentNode == NULL) {
		printf("\nDanh sach lien ket rong.\n");
		return;
	}
	printf("\nDanh sach lien ket: ");
	while (currentNode != NULL) {
		printf("%d ", currentNode->data);
		currentNode = currentNode->next;
	}
	printf("\n");
	return;
}

int main() { // hàm main để chạy chương trình
	textcolor(10);
	int choose, data;
	while (1) {
		printf("Chon mot lua chon:\n");
		printf("1. Chen phan tu vao dau danh sach.\n");
		printf("2. Chen phan tu vao cuoi danh sach.\n");
		printf("3. Xuat danh sach.\n");
		printf("0. Thoat chuong trinh.\n");
		printf("Lua chon: ");
		scanf_s("%d", &choose);

		switch (choose) {
		case 1:
			printf("Nhap phan tu can chen vao dau: ");
			scanf_s("%d", &data);
			insertHead(data);
			break;
		case 2:
			printf("Nhap phan tu can chen vao cuoi: ");
			scanf_s("%d", &data);
			insertTail(data);
			break;
		case 3:
			printList();
			break;
		case 0:
			printf("Chuong trinh ket thuc.\n");
			exit(0);
		default:
			printf("Lua chon khong hop le. Vui long chon lai.\n");
		}
	}
	return 0;
}