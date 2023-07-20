#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
void textcolor(int x) {
	HANDLE v = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleTextAttribute(v, x);
}
typedef struct linkedlist
{
	int data;
	struct linkedlist* next;
}node;
typedef struct list
{
	node* head;
	node* tail;
}list;
node* createnode(int x) {
	node* p = (node*)malloc(sizeof(node));
	if (p == NULL)
	{
		printf("Khong du bo nho de cap phat!\n");
		return NULL;
	}
	p->data = x;
	p->next = NULL;
	return p;
}
void headtail(list* l) {
	l->head = NULL;
	l->tail = NULL;
}
void InsertHead(list* l, node* p) {
	if (l->head == NULL)
	{
		l->head = p;
		l->tail = p;
	}
	else
	{
		p->next = l->head;
		l->head = p;
	}
}
void InsertTail(list* l, node* p) {
	if (l->tail == NULL)
	{
		l->head = p;
		l->tail = p;
	}
	else
	{
		l->tail = p->next;
		l->tail = p;
	}
}
void printList(node* i) {
	while (i != NULL) {
		printf("%d -> ", i->data);
		i = i->next;
	}
	printf("NULL\n");
}
void duyet(node* p) {
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
}
int count(node* head) {
	int dem = 0;
	while (head != NULL)
	{
		dem++;
		head = head->next;
	}
	return dem;
}
int main() {
	textcolor(10);
	list l;
	int n;
	createnode(&l);
	printf("Nhap so luong node can them: ");
	scanf_s("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		int x;
		printf("Nhap gia tri so nguyen: ");
		scanf_s("%d", &x);
		node* p = createnode(x);
		InsertTail(&l, p);
	}
	printf("DANH SACH LIEN KET DON\n");
	printList(&l);
	return 0;
}