#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <iomanip>

void textcolor(int x) {
	HANDLE y = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(y, x);
}
void flush_file(std::ifstream& f) { //Ham xoa dau ENTER trong file
	char c;
	while (f.get(c) && c != '\n' && c != std::ifstream::traits_type::eof());
}
struct DoAn {
	char MaDoAn[20];
	char MaSinhVien[20];
	std::string TenGiaoVienHD;
	int diemso;
};
struct NODE {
	DoAn do_an;
	struct NODE* next;
	struct NODE* prev;
};
struct LIST {
	NODE* head, * tail;
};
void initList(LIST& list) {
	list.head = NULL;
	list.tail = NULL;
}
NODE* initNode(DoAn do_an) {
	NODE* newNode = new NODE;
	newNode->do_an.diemso = do_an.diemso;
	strcpy(newNode->do_an.MaDoAn, do_an.MaDoAn);
	strcpy(newNode->do_an.MaSinhVien, do_an.MaSinhVien);
	newNode->do_an.TenGiaoVienHD = do_an.TenGiaoVienHD;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}
int isEmpty(LIST *list) {
	return list->head && list->tail ? 0 : 1 ;
}
void insertTail(LIST* list, DoAn do_an) {
	NODE* node = initNode(do_an);
	if (isEmpty(list)) {
		list->head = node;
		list->tail = node;
	}
	else {
		node->prev = list->tail;
		list->tail->next = node;
		list->tail = node;
	}
}
void printNode(LIST* list) {
	NODE* node;
	const int size = 17;
	std::cout << std::left << std::setw(size) << "Ma Do An" << std::setw(size) << "Ma Sinh Vien" << std::setw(size) << "Ten Giang Vien" << "Diem So\n";
	for (node = list->head; node != NULL; node = node->next)
		std::cout << std::left << std::setw(size) << node->do_an.MaDoAn << std::setw(size) << node->do_an.MaSinhVien << std::setw(size) << node->do_an.TenGiaoVienHD << std::setw(size) << node->do_an.diemso << '\n' ;
	delete node;
}
//Yeu cau 1
int inputDoAn(LIST *list, DoAn &do_an, int& n, char file_input[]) {
	std::ifstream file;
	file.open(file_input);
	if (!file) {
		std::cout << "File khong ton tai.\n";
		return 0;
	}
	file >> n;
	for (int i = 0; i < n; i++) {
		file >> do_an.MaDoAn;
		file >> do_an.MaSinhVien;
		flush_file(file);
		getline(file, do_an.TenGiaoVienHD);
		file >> do_an.diemso;
		flush_file(file);
		insertTail(list, do_an);
	}
	file.close();
	return 1;
}
void outputDoAn(LIST *list, int& n) {
	std::cout << "So luong do an: ";
	textcolor(9);
	std::cout << n << "\n";
	std::cout << "Danh sach cac do an: \n\n";
	textcolor(14);
	printNode(list);
}
//Yeu cau 2
void lietke(LIST *list, int n) {
	int dem = 0;
	std::string tengiaovien;
	NODE* node;
	for (node = list->head; node != NULL; node = node->next) {
		node->do_an.TenGiaoVienHD = tengiaovien;
		if (node->do_an.TenGiaoVienHD == tengiaovien)
			for (int i = 0; i < n; i++)
				if (node->do_an.TenGiaoVienHD.compare(tengiaovien) == 0) {
					dem++;
					std::cout << dem << std::endl;
				}
		if (dem > 1)
			std::cout << tengiaovien << std::endl;
		dem = 0;
	}
}
//Yeu cau 3
int timmax(DoAn do_an[], int n) {
	int max = do_an[0].diemso;
	for (int i = 0; i < n; i++)
		if (do_an[i].diemso > max)
			max = do_an[i].diemso;
	return max;
}
void xuatmasinhvien(DoAn do_an[], int n) {
	for (int i = 0; i < n; i++) {
		if (do_an[i].diemso == timmax(do_an, n)) {
			std::cout << do_an[i].MaSinhVien << '\n';
		}
	}
}
//Yeu cau 4
void lietke4(DoAn do_an[], int n) {
	for (int i = 0; i < n; i++)
		std::cout << do_an[i].TenGiaoVienHD << std::endl;
}
void clearFile(char filename[]) {
	std::ofstream ofs;
	ofs.open(filename, std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}
int select() {
	int o;
	std::cout << "Moi ban nhap yeu cau (Nhap so 0 de thoat chuong trinh): ";
	std::cin >> o;
	while (!(o >= 0 && o <= 6)) {
		std::cout << "Yeu cau khong hop le, vui long ban nhap lai: ";
		std::cin >> o;
	}
	return o;
}
void program() {
	textcolor(12);
	DoAn do_an;
	LIST list;
	char file_input[] = "DoAn.txt";
	int n = 0;
	int o = select();
	initList(list);
	switch (o) {
		case 1: {
			textcolor(14);
			if (inputDoAn(&list, do_an, n, file_input))
				std::cout << "Nhap danh sach cac do an thanh cong" << std::endl;
			outputDoAn(&list, n);
		}break;
		case 2: {
			textcolor(9);
			inputDoAn(&list, do_an, n, file_input);
			std::cout << "Giao vien tham gia huong dan tu 2 do an tro len:\n";
			lietke(&list, n);
		}break;
		case 3: {
			textcolor(11);
			inputDoAn(&list, do_an, n, file_input);
			std::cout << "Cac ma sinh vien co diem do an lon nhat la: \n";
			xuatmasinhvien(&do_an, n);
		}break;
		case 4: {
			textcolor(10);
			inputDoAn(&list, do_an, n, file_input);
			std::cout << "Cac giao vien co huong dan do an trong danh sach: \n";
			lietke4(&do_an, n);
		}break;
		case 5: {
			inputDoAn(&list, do_an, n, file_input);

		}break;
		case 6: {
			inputDoAn(&list, do_an, n, file_input);

		}break;
		default: {
			std::cout << "Thoat chuong trinh trong ";
			for (int i = 3; i >= 1; i--) {
				std::cout << i;
				Sleep(1000);
				std::cout << '\b';
			}
			Sleep(500);
			exit(0);
		}
		break;
	}
}
int main() {
	while (true)
		program();
	system("pause");
	return 0;
}
