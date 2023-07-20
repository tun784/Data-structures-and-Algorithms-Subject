#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <Windows.h>
// Hàm đổi màu
void textcolor(int x) {
	HANDLE y = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(y, x);
}
//Hàm xoá dấu ENTER
void flush_stdin() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}
// Cấu trúc sinh viên
typedef struct SinhVien {
	char name[50];
	int MSSV;
}SV;
// Danh sách liên kết
typedef struct node {
	SV sinhvien;
	struct NODE* next;
}NODE;
// Khai báo 2 con trỏ head và tail
typedef struct LIST {
	NODE* head, * tail;
}LIST;
// Hàm tạo node
NODE *createNode(char ten, int data) {
	NODE* p = (NODE*)malloc(sizeof(NODE));
	p->sinhvien.MSSV = data;
	strcpy(p->sinhvien.name, ten);
	p->next = NULL;
	return p;
}
//Chèn đầu
void insertHead(LIST *list, char ten, int x) {
	NODE *node = createNode(ten,x);
	if (list->head==NULL)
	{
		list->head = list->tail = node;
		return;
	}
	node->next = list->head;
	list->head = node;
}
//Chèn cuối
void insertTail(LIST* list, char ten, int x) {
	NODE* node = createNode(ten,x);
	if (list->head==NULL)
	{
		list->head = list->tail = node;
		return;
	}
	list->tail->next = node;
	list->tail = node;
}
//Hàm in ra màn hình
void printLinkedList(LIST *list) {
	if (list->head==NULL)
	{
		printf("List is empty.\n");
		return;
	}
	NODE* node = list->head;
	while (node!=NULL)
	{
		puts(node->sinhvien.name);
		printf(" - %d \n", node->sinhvien.MSSV);
		node = node->next;
	}
}
//Hàm đếm số lượng node
int count(NODE* node) {
	int dem = 0;
	while (node != NULL)
	{
		dem++;
		node = node->next;
	}
	return dem;
}
// Hàm để xoá một phần tử trong danh sách liên kết
void delete(LIST* list, int x) {
	if (list->head == NULL) {
		printf("List is empty\n");
		return;
	}
	NODE* previous_node = NULL, * current_node = list->head;
	while (current_node != NULL) {
		if (current_node->sinhvien.MSSV == x) {
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
// Hàm để chèn một phần tử vào vị trí bất kỳ trong danh sách liên kết 
void insertNode(LIST* list, char ten[], int x, int pos) {
	if (pos < 1) {
		printf("Vi tri chen khong hop le!\n");
		return;
	}
	if (pos == 1) {
		insertHead(list, ten, x);
		return;
	}
	NODE* previous_node = NULL, * current_node = list->head;
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
	NODE* node = createNode(ten, x);
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
//Tiêu đề
void title() {
	printf("Loading");
	for (int i = 1; i < 10; i++) {
		Sleep(50);
		printf(" *");
	}
	printf("\nCompleted \a");
	Sleep(1400);
	system("cls");
	printf("DANH SACH LIEN KET\n");
	printf("Luu du lieu sinh vien.\n");
	printf("Bao gom: \n");
	printf("1. Ho va ten.\n2. ma so sinh vien.\n");
}
// Các yêu cầu
void requiremennts() {
	printf("1. Chen phan tu dau.\n");
	printf("2. Chen phan tu cuoi.\n");
	printf("3.Chen phan tu giua vao vi tri bat ky.\n");
	printf("4.Xoa phan tu bat ki.\n");
	printf("5.Dem so luong sinh vien\n");
}
//Chọn bài cần làm
int selecttest() {
	int o;
	printf("VUI LONG CHON YEU CAU: ");
	scanf("%d", &o);
	while (o < 0)
	{
		printf("Yeu cau khong hop le, vui long chon lai: ");
		scanf("%d", &o);
	}
	return o;
}
//Chọn số lượng node
int numberofnode() {
	int soluongnode;
	printf("NHAP SO LUONG SINH VIEN CAN TAO: ");
	scanf("%d", &soluongnode);
	while (soluongnode <= 0)
	{
		printf("so luong phan tu khong hop le, vui long nhap lai: ");
		scanf("%d", &soluongnode);
	}
	return soluongnode;
}
// Nhập danh sách liên kết
void inputLinkedList(int n) {
	LIST list;
	int  x;
	char ten[50];
	for (int i = 1; i <= n; i++)
	{
		printf("Sinh vien thu %d: \n", i);
		printf("Ho va ten sinh vien: "); 
		flush_stdin();
				gets(ten);
		printf("MSSV: "); 
			scanf("%d", &x);
		insertTail(&list, ten, x);
	}
}
void mainprogram() {
	int numbernode = numberofnode();
	int luachon = selecttest();
	int x, n, xdel, y, pos;
	char ten[50];
	LIST list;
	list.head = list.tail = NULL;

	inputLinkedList(numbernode);
	requiremennts();
	switch (luachon)
	{
		case 1:
			{
				printf("Ho va ten sinh vien: ");
				flush_stdin();
				gets(ten);
				printf("MSSV: ");
				scanf("%d", &x);
				insertHead(&list, ten, x); 
			}
			break;
		case 2: 
			{
				printf("Ho va ten sinh vien: ");
				flush_stdin();
				gets(ten);
				printf("MSSV: ");
				scanf("%d", &x);
				insertTail(&list, ten, x); 
			}
			break;
		case 3: {
			printf("nhap phan tu can chen va vi tri muon chen\n");
			printf("Ho va ten sinh vien: ");
			flush_stdin();
			gets(ten);
			printf("MSSV: ");
			scanf("%d", &x);
			scanf("%d%d", &y, &pos);
			insertNode(&list, ten, y, pos);
			printLinkedList(&list);
			printf("\n");
		}
			break;
		case 4: {
			printf("nhap phan tu can xoa: ");
			scanf("%d", &xdel);
			delete(&list, xdel);
			printf("danh sach lien ket sau khi xoa phan tu %d: ", xdel);
			printLinkedList(&list);
			printf("\n");
		}
			break;
		default: exit(0);
			break;
	}
}
int main() {
	textcolor(10);
	while (1) {
		title();
		mainprogram();
	}
	return 0;
}
