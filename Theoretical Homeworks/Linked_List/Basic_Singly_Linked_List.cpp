#include <iostream>
using namespace std;
struct NODE {
	int data;
	struct NODE* next;
};
NODE* createNode(int x) {
	NODE* pointer = new NODE;
	pointer->data = x;
	pointer->next = nullptr;
	return pointer;
}
void duyet(NODE* pointer) {
	while (pointer != NULL)
	{
		cout << pointer->data << ' ';
		pointer = pointer->next;
	}
}
int count(NODE* pointer) {
	int dem = 0;
	while (pointer != NULL)
	{
		++dem;
		pointer = pointer->next;
	}
	return dem;
}
void insertHead(NODE** head, int x) {
	NODE* pointer = createNode(x);
	pointer->next = *head;
	*head = pointer;
}
int main() {

	system("pause");
	return 0;
}