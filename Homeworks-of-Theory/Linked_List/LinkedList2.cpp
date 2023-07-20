#include <iostream>
#include <string>
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
	std::string name;
	int MSSV;
}SV;
// Danh sách liên kết
struct NODE {
	SV sinhvien;
	struct NODE* next;
};
// Khai báo 2 con trỏ head và tail
struct LIST {
	NODE* head, * tail;
};
// Hàm tạo pointer
NODE* initNode(std::string ten, int data) {
	NODE* pointer = new NODE;
	pointer->sinhvien.MSSV = data;
	pointer->sinhvien.name = ten;
	pointer->next = NULL;
	return pointer;
}
//Chèn đầu
void insertHead(LIST* llist, std::string ten, int x) {
	NODE* pointer = initNode(ten, x);
	if (llist->head == NULL)
	{
		llist->head = llist->tail = pointer;
		return;
	}
	pointer->next = llist->head;
	llist->head = pointer;
}	
//Chèn cuối
void insertTail(LIST* llist, std::string ten, int x) {
	NODE* pointer = initNode(ten, x);
	if (llist->head == NULL)
	{
		llist->head = llist->tail = pointer;
		return;
	}
	llist->tail->next = pointer;
	llist->tail = pointer;
}
// Hàm để chèn một phần tử vào vị trí bất kỳ trong danh sách liên kết 
void insertNode(LIST* llist, std::string ten, int x, int pos) {
	if (pos < 1) {
		std::cout << "Vi tri chen khong hop le!" << std::endl;
		return;
	}
	if (pos == 1) {
		insertHead(llist, ten, x);
		return;
	}
	NODE* previous_pointer = NULL, * current_pointer = llist->head;
	int i = 1;
	while (current_pointer != NULL && i < pos) {
		previous_pointer = current_pointer;
		current_pointer = current_pointer->next;
		i++;
	}
	if (i < pos) {
		std::cout << "Vi tri chen khong hop le!" << std::endl;
		return;
	}
	NODE* pointer = initNode(ten, x);
	if (previous_pointer == NULL) {
		llist->head = pointer;
	}
	else {
		previous_pointer->next = pointer;
	}
	pointer->next = current_pointer;
	if (current_pointer == NULL) {
		llist->tail = pointer;
	}
}
// Hàm để xoá một phần tử trong danh sách liên kết
void deleteNode(LIST* llist, int x) {
	if (llist->head == NULL) {
		std::cout << "Danh sach rong" << std::endl;
		return;
	}
	NODE* previous_pointer = NULL, * current_pointer = llist->head;
	while (current_pointer != NULL) {
		if (current_pointer->sinhvien.MSSV == x) {
			if (previous_pointer == NULL) {
				llist->head = current_pointer->next;
				if (llist->head == NULL) {
					llist->tail = NULL;
				}
			}
			else {
				previous_pointer->next = current_pointer->next;
				if (previous_pointer->next == NULL) {
					llist->tail = previous_pointer;
				}
			}
			free(current_pointer);
			return;
		}
		previous_pointer = current_pointer;
		current_pointer = current_pointer->next;
	}
}
//Hàm in ra màn hình
void printLinkedList(LIST* llist) {
	NODE* pointer = llist->head;
	if (llist->head != NULL)
	{
		while (pointer != NULL)
		{
			textcolor(10);
			std::cout << "Ho va ten: ";
			textcolor(7);
			std::cout << pointer->sinhvien.name << '\t';
			textcolor(10);
			std::cout << "MSSV: ";
			textcolor(7);
			std::cout << pointer->sinhvien.MSSV << " ";
			pointer = pointer->next;
			std::cout << std::endl;
		}
	}
	std::cout << "\a\n";
}
//Hàm đếm số lượng pointer
int count(LIST* llist) {
	NODE* pointer = llist->head;
	int dem = 0;
	while (pointer != NULL)
	{
		pointer = pointer->next;
		dem++;
	}
	return dem;
}

//Tiêu đề
void title() {
	std::cout << "\aLoading ";
	for (int i = 1; i <= 9; i++) {
		Sleep(15);
		std::cout << i << "%";
		for (int j = 1; j <= 2; j++) {
			std::cout << '\b';
		}
	}
	for (int i = 10; i <= 99; i++)
	{
		Sleep(10);
		std::cout << i << "%"; 
		for (int j = 1; j <= 3; j++) {
			std::cout << '\b';
		}
	}
	std::cout << "100%";
	for (int i = 1; i <= 4; i++) {
		std::cout << '\b';
	}
	std::cout << "\nCompleted Loading...\a\n";
	Sleep(1000);
	std::cout << "DANH SACH LIEN KET\n";
	std::cout << "Luu du lieu sinh vien.\n";
	std::cout << "Bao gom: \n";
	std::cout << "1. Ho va ten.\n2. ma so sinh vien.\n";
}
// Các yêu cầu
void requiremennts() {
	std::cout << "1. Chen phan tu dau.\n";
	std::cout << "2. Chen phan tu cuoi.\n";
	std::cout << "3.Chen phan tu giua vao vi tri bat ky.\n";
	std::cout << "4.Xoa phan tu bat ki.\n";
	std::cout << "5.Dem so luong sinh vien\n";
}
//Chọn bài cần làm
int selecttest() {
	int o;
	std::cout << "VUI LONG CHON YEU CAU: ";
	std::cin >> o;
	while (o < 0) {
		std::cout << "Yeu cau khong hop le, vui long chon lai: ";
		std::cin >> o;
	}
	return o;
}
//Chọn số lượng pointer
int numberofpointer() {
	int soluongpointer;
	std::cout << "NHAP SO LUONG SINH VIEN CAN TAO: ";
	std::cin >> soluongpointer;
	while (soluongpointer <= 0) {
		std::cout << "so luong phan tu khong hop le, vui long nhap lai: ";
		std::cin >> soluongpointer;
	}
	return soluongpointer;
}
// Nhập danh sách liên kết
void inputLinkedList(LIST* llist, int n) {
	std::string ten;
	int  x;
	for (int i = 1; i <= n; i++)
	{
		std::cout << "Sinh vien thu " << i << ": " << std::endl;
		std::cout << "Ho va ten sinh vien: ";
		flush_stdin();
		getline(std::cin, ten);
		std::cout << "MSSV: ";
		std::cin >> x;
		insertTail(llist, ten, x);
	}
}
//Chương trình chính
void mainprogram() {
	int numberpointer = numberofpointer();
	int x, n, xdel, y, pos;
	std::string ten;
	LIST llist;
	llist.head = llist.tail = NULL;

	inputLinkedList(&llist, numberpointer);
	requiremennts();
	int luachon = selecttest();
	switch (luachon)
	{
		case 1:
		{
			std::cout << "Ho va ten sinh vien: ";
			flush_stdin();
			getline(std::cin,ten);
			std::cout << "MSSV: ";
			std::cin >> x;
			insertHead(&llist, ten, x);
			printLinkedList(&llist);
		}
			break;
		case 2:
		{
			std::cout << "Ho va ten sinh vien: ";
			flush_stdin();
			getline(std::cin,ten);
			std::cout << "MSSV: ";
			std::cin >> x;
			insertTail(&llist, ten, x);
			printLinkedList(&llist);
		}
		break;
		case 3: {
			std::cout << "nhap phan tu can chen va vi tri muon chen" << std::endl;
			std::cout << "Ho va ten sinh vien: ";
			flush_stdin();
			getline(std::cin,ten);
			std::cout << "MSSV: ";
			std::cin >> x;
			std::cin >> y >> pos;
			insertNode(&llist, ten, y, pos);
			printLinkedList(&llist);
			std::cout << std::endl;
		}
			  break;
		case 4: {
			std::cout << "nhap phan tu can xoa: ";
			std::cin >> xdel;
			deleteNode(&llist, xdel);
			std::cout << "danh sach lien ket sau khi xoa phan tu " << xdel << " la: " << std::endl;
			printLinkedList(&llist);
			std::cout << std::endl;
		}
			  break;
		case 5: {
			int dem = count(&llist);
			std::cout << "So luong sinh vien la " << dem << '\a' << std::endl;
		}
			break;
		default: {
			char thoatct;
			std::cout << "Ban muon thoat khoi chuong trinh? (y/n) ";
			std::cin >> thoatct;
			switch (thoatct) {
				case 'y':
				case 'Y': 
				case 'yes':
				case 'Yes': {
					std::cout << "Thoat chuong trinh trong ";
					for (int i = 1; i <= 3; i++) {
						std::cout << i << " giay";
						Sleep(1000);
						for (int j = 1; j <= 6; j++) {
							std::cout << '\b';
						}
					}
						std::cout << std::endl << "DANG THOAT CHUONG TRINH" << std::endl;
						Sleep(900);
				}
					break;
				case 'n':
				case 'N':
				case 'No':
				case 'no':
					return mainprogram();
					break;
				default:
					std::cout << "ERROR"; exit(0);
					break;
			}
			exit(0); 
		}
			break;
	}
}
int main() {
	textcolor(7);
	// Change background color to white
	//std::cout << "\033[47m";
	// Change text color to white
	//std::std::cout << "\033[37m";
	system("cls");
	title();
	mainprogram();
	while (true) {
		title();
		mainprogram();
	}
	system("pause");
	// Reset colors to default
	std::cout << "\033[0m";
	return 0; 
}