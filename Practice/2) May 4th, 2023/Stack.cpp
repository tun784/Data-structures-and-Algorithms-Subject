#include <iostream>
#include <string>
#include <fstream>
//Hàm xoá dấu ENTER
void flush_stdin() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}
struct NODE {
	int data;
	NODE* next;
};
struct STACK {
	NODE* top;
};
int isEmpty(STACK* s) {
	if (s->top == nullptr)
		return 1; //Stack rỗng
	else
		return 0; //Stack không rỗng
}

NODE* initNODE(int data) {
	NODE* pointer = new NODE;
	if (pointer == NULL) {
		std::cout << "Not enough memory !" << std::endl;
		system("pause");
		return NULL;
	}
	pointer->data = data;
	pointer->next = NULL;
	return pointer;
}
int isFull(STACK* s) {
	NODE* pointer = initNODE(1);
	if (pointer == NULL) //Không đủ bộ nhớ
		return 1; //Stack đầy
	else { //Còn đủ bộ nhớ
		delete pointer;
		return 0; //Stack không đầy
	}
}
int push(STACK* s, int data) {
	NODE* pointer = initNODE(data);
	if (pointer = NULL)
		return 0; //Thực hiện không thành công
	if (isEmpty(s) == 1)
		s->top = pointer;
	else {
		pointer->next = s->top;
		s->top = pointer;
	}
	return 1; //Thực hiện thành công
}
int pop(STACK* s, int* data) {
	if (isEmpty(s) == 1) // Stack rỗng
		return 0; //Thực hiện không thành công
	NODE* pointer = s->top;
	s->top = s->top->next;
	*data = pointer->data;
	delete pointer;
	return 1;
}
int getTop(STACK* s, int* data) {
	if (isEmpty(s) == 1) // Stack rỗng
		return 0; //Thực hiện không thành công
	*data = s->top->data; //Lấy thông tin của nút ở đỉnh Stack
	return 1; //Thực hiện thành công
}
void printSTACK(STACK* s) {
	NODE* pointer = s->top;
	while (pointer != NULL) {
		std::cout << pointer->data << " ";
		pointer = pointer->next;
	}
}

int luachon() {
	int o;
	std::cout << "Ban muon chon bai nao (hoac nhap so 0 de thoat chuong trinh) ? ";
	std::cin >> o;
	while (!(o >= 0 && o <= 6)) {
		std::cout << "Ban nhap khong hop le, vui long nhap lai: ";
		std::cin >> o;
	}
	return o;
}
void program() {
	int o = luachon();
	STACK s;
	int data;

	switch (o)
	{
		case 1: {
			std::cout << "Danh sach cac node trong Stack:\n";
			printSTACK(&s);
			std::cout << std::endl;
		}break;
		case 2: {
			if (!isEmpty(&s))
				std::cout << "Stack rong.\n";
			else
				std::cout << "Stack khong rong.\n";
		}break;
		case 3: {
			if (isFull(&s))
				std::cout << "Stack day.\n";
			else
				std::cout << "Stack khong day.\n";
		}break;
		case 4: {
			std::cout << "Nhap so nguyen bat ky: ";
			std::cin >> data;
			push(&s, data);
			std::cout << '\n';
		}break;
		case 5: {
			std::cout << "Nhap phan tu muon xoa: ";
			std::cin >> data;
			std::cout << "Lay phan tu " << data << " ra khoi Stack.\n";
			pop(&s,&data);
		}break;
		case 6: {
			getTop(&s, &data);
			std::cout << "Phan tu o dinh Stack la " << data << '\n';
		}break;
		default: exit(0);
			break;
	}
}
int main() {
	while (true) {
		program();
	}
	system("pause");
	return 0;
}
