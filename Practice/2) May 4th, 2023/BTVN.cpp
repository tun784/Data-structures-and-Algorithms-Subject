#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <Windows.h>
#include <iomanip>
#define MaHH 5

void textcolor(int x) {
	HANDLE y = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(y, x);
}
void flushFile(std::ifstream &f) {
	char c;
	while (f.get(c) && c != '\n' && c != std::ifstream::traits_type::eof());
}
void flushStdin() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}
void title() {
	std::cout << "\tBAI TAP DU LIEU HANG HOA:\n";
	std::cout << "\t\t1) Xuat danh sach hang hoa.\n";
	std::cout << "\t\t2) Dem co bao nhieu hang hoa co don gia > 2000.\n";
	std::cout << "\t\t3) Tinh tong tien cua tat ca hang hoa tren.\n";
	std::cout << "\t\t4) Xuat ten hang hoa co so luong < 7.\n";
	std::cout << "\t\t5) Sap xep danh sach hang hoa theo thu tu don gia tang dan.\n";
	std::cout << "\t\t6) Sap xep danh sach hang hoa theo thu tu ma hang hoa theo A-Z.\n";
	std::cout << "\t\t7) Them 1 hang hoa vao cuoi danh sach (luu y ma hang khong duoc giong nhau).\n";
	std::cout << "\t\t8) Xoa hang hoa thuoc loai Mi ra khoi danh sach.\n";
}
struct HangHoa {
	char MaHangHoa[MaHH];
	std::string TenHangHoa;
	unsigned int SoLuong;
	unsigned long DonGia;
};
struct NODE {
	HangHoa hanghoa;
	NODE* next;
	NODE* prev;
};
typedef struct DOUBLE_LINKED_LIST {
	NODE* head, * tail;
}LL;

void initLL(LL& list) {
	list.head = NULL;
	list.tail = NULL;
}
NODE* createNode(HangHoa &data) {
	NODE* newNode = new NODE;
	strcpy(newNode->hanghoa.MaHangHoa, data.MaHangHoa);
	newNode->hanghoa.TenHangHoa = data.TenHangHoa;
	newNode->hanghoa.SoLuong = data.SoLuong;
	newNode->hanghoa.DonGia = data.DonGia;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}
int isEmpty(LL *list) {
	return list->head == NULL && list->tail == NULL ? 1 : 0;
}
// Insert head function
void insertHead(LL* list, HangHoa &data) {
	NODE* pointer = createNode(data);
	if (isEmpty(list)) {
		list->head = pointer;
		list->tail = pointer;
	}
	else {
		pointer->next = list->head;
		list->head->prev = pointer;
		list->head = pointer;
	}
}
void insertTail(LL* list, HangHoa &data) {
	NODE* pointer = createNode(data);
	if (isEmpty(list)) {
		list->head = pointer;
		list->tail = pointer;
	}
	else {
		pointer->prev = list->tail;
		list->tail->next = pointer;
		list->tail = pointer;
	}
}
void insertMiddle(LL* list, HangHoa &data, NODE* prevNode) {
	NODE* pointer = createNode(data);
	if (prevNode == NULL) {
		insertHead(list, data);
	}
	else {
		pointer->next = prevNode->next;
		pointer->prev = prevNode;
		prevNode->next = pointer;
		if (pointer->next != NULL) {
			pointer->next->prev = pointer;
		}
		else {
			list->tail = pointer;
		}
	}
}
NODE* findNode(LL* list, HangHoa &data) {
	NODE* currNode = list->head;
	while (currNode != NULL) {
		if (currNode->hanghoa.MaHangHoa == data.MaHangHoa) {
			return currNode;
		}
		currNode = currNode->next;
	}
	return NULL;
}
// Delete node function
void deleteNode(LL* list, NODE* node) {
	if (node == NULL)
		return;
	if (node == list->head) {
		list->head = node->next;
		if (list->head != NULL)
			list->head->prev = NULL;
		else
			list->tail = NULL;
	}
	else if (node == list->tail) {
		list->tail = node->prev;
		list->tail->next = NULL;
	}
	else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	delete node;
}

int readfromFile(LL* list, unsigned int& soluong, char file_input[], HangHoa& data) {
	std::ifstream file;
	file.open(file_input);
	if (!file) {
		std::cout << "Loi mo file hoac file khong ton tai.\n";
		return 0;
	}
	file >> soluong;
	for (unsigned int i = 0; i < soluong; i++) {
		flushFile(file);
		file >> data.MaHangHoa;
		flushFile(file);
		getline(file, data.TenHangHoa);
		file >> data.SoLuong;
		file >> data.DonGia;
		insertTail(list, data);
	}
	file.close();
	return soluong;
}
//Bai 1
void printdata(LL* list) {
	const int size = 80;
	const int setw1 = 14;
	const int setw2 = 27;
	int k = 0;
	NODE* node;
	std::cout << "\t\t.";
	for (int i = 0; i < size; i++)
		std::cout << "=";
	std::cout << ".\n";
	std::cout << std::left << std::setw(13) << "\t\t|| STT ||" << std::setw(setw1) << "Ma Hang Hoa" << std::setw(setw2) << "Ten Hang Hoa" << std::setw(setw1) << "So Luong" << std::setw(setw1) << "Don Gia" <<"||\n";
	for (node = list->head; node != NULL; node = node->next) {
		k++;
		std::cout << "\t\t||  " << k << "  ||  " << std::left << std::setw(setw1) << node->hanghoa.MaHangHoa << std::setw(setw2) << node->hanghoa.TenHangHoa << std::setw(setw1) << node->hanghoa.SoLuong << std::setw(setw1) << node->hanghoa.DonGia << "||\n";
	}
	std::cout << "\t\t*";
	for (int i = 0; i < size; i++)
		std::cout << "=";
	std::cout << "*\n";
	delete node;
}
//Bai 2
unsigned int demhanghoa(LL* list) {
	unsigned int dem = 0;
	NODE* node;
	for (node = list->head; node != NULL; node = node->next)
		if (node->hanghoa.DonGia > 2000)
			dem++;
	delete node;
	return dem;
}
//Bai 3
unsigned int tongtien(LL* list) {
	unsigned int tien = 0;
	NODE* node;
	for (node = list->head; node != NULL; node = node->next)
		tien += node->hanghoa.DonGia * node->hanghoa.SoLuong;
	delete node;
	return tien;
}
//Bai 4
void xuattenhanghoa(LL* list) {
	unsigned int k=1;
	NODE* node;
	for (node = list->head; node != NULL; node = node->next) 
		if (node->hanghoa.SoLuong < 7) {
			std::cout << "\t\t" << k << ") " << node->hanghoa.TenHangHoa << std::endl;
			k++;
		}
	delete node;
}
//Bai 5
void swap(NODE* node_a, NODE* node_b) {
	NODE temp;
	temp.hanghoa = node_a->hanghoa;
	node_a->hanghoa = node_b->hanghoa;
	node_b->hanghoa = temp.hanghoa;
}
void sapxepdongia(LL* list) {
	NODE* currnode = list->head;
	NODE* nextnode = currnode->next;
	while (currnode != NULL) {
		while (nextnode != NULL) {
			if (currnode->hanghoa.DonGia > nextnode->hanghoa.DonGia)
				swap(currnode, nextnode);
			nextnode=nextnode->next;
		}
		currnode = currnode->next;
	}
}
//Bai 6
void sapxepmahanghoa(LL* list) {
	NODE* currnode = list->head;
	NODE* nextnode = currnode->next;
	while (currnode != NULL) {
		while (nextnode != NULL) {
			if (strcmp(currnode->hanghoa.MaHangHoa, nextnode->hanghoa.MaHangHoa) > 0)
				swap(currnode, nextnode);
				nextnode = nextnode->next;
			}
		currnode = currnode->next;
	}
}
//Bai 7
void chenvaoFile(LL* list, unsigned int& soluong, char file_input[]) {
	NODE* node;
	std::ofstream file;
	//file.open(file_input, std::ios::app);
	file.open(file_input, std::ofstream::out);
	if (!file) {
		std::cout << "Loi mo file hoac file khong ton tai.\n";
		return;
	}
	file << soluong << "\n";
	for (node = list->head; node != NULL; node = node->next) {
		file << node->hanghoa.MaHangHoa << "\n";
		file << node->hanghoa.TenHangHoa << "\n";
		file << node->hanghoa.SoLuong << "\n";
		file << node->hanghoa.DonGia << "\n";
	}
	file.close();
	delete node;
}
void themhanghoa(LL * list,  unsigned int &soluong, HangHoa &data, char file_input[]) {
	const int setw1 = 14;
	const int setw2 = 27;
	NODE* tim;
	int ketqua = 0;

	std::cout << "\t\t\tMa hang hoa: ";
	std::cin >> data.MaHangHoa;

	for (tim = list->head; tim != NULL; tim = tim->next) {
		if ((std::string(tim->hanghoa.MaHangHoa).compare(data.MaHangHoa)) == 0) {
			ketqua = 1;
		}
		else
			ketqua = 0;
	}
	while (ketqua) {
		std::cout << "\t\t\tXin loi, ban da nhap trung ma hang hoa voi mat hang co san trong kho.\n\t\t\t- Xin vui long nhap lai: ";
		std::cin >> data.MaHangHoa;
		for (tim = list->head; tim != NULL; tim = tim->next) {
			if ((std::string(tim->hanghoa.MaHangHoa).compare(data.MaHangHoa)) == 0) {
				ketqua = 1;
			}
			else
				ketqua = 0;
		}
	}
	std::cin.ignore();
	std::cout << "\t\t\tTen hang hoa: ";
	getline(std::cin, data.TenHangHoa);
	std::cout << "\t\t\tSo luong: ";
	std::cin >> data.SoLuong;
	std::cout << "\t\t\tDon gia: ";
	std::cin >> data.DonGia;

	std::cout << "\n\tBan da them hang hoa co cac thong tin sau: \n";
	std::cout << "\t\t" << std::left << std::setw(setw1) << "Ma Hang Hoa" << std::setw(setw2) << "Ten Hang Hoa" << std::setw(setw1) << "So Luong" << std::setw(setw1) << "Don Gia" << "\n";
	std::cout << "\t\t" << std::left << std::setw(setw1) << data.MaHangHoa << std::setw(setw2) << data.TenHangHoa << std::setw(setw1) << data.SoLuong << std::setw(setw1) << data.DonGia << "\n";
	
	insertTail(list, data);
	
	textcolor(12);
	std::cout << "\tSo luong mat hang tang len thanh ";
	textcolor(14);
	std::cout << soluong;
	textcolor(12);
	std::cout << " mat hang.\n";
	textcolor(14);
	soluong++;
	chenvaoFile(list, soluong, file_input);
	delete tim;
}
//Bai 8
void xoahanghoa(LL* list, char Loai[], unsigned int soluong, char file_input[]) {
	NODE* node;
	std::cout << sizeof(Loai) << std::endl;
	int sizeLoai = sizeof(Loai) / sizeof(Loai[0]);
	unsigned int n=0;
	for (node = list->head; node != NULL; node = node->next)
		if (strncmp(node->hanghoa.TenHangHoa.c_str(), Loai, sizeLoai) == 0) {
			deleteNode(list, node);
			n++;
		}
	unsigned int soconlai = soluong - n;
		std::cout << "\t\t\t\tDa xoa them " << soluong << " mat hang.\n";
	chenvaoFile(list, soluong, file_input);
	delete node;
}
int selection() {
	int o;
	std::cout << "\n\tBan muon chon bai nao (nhan so 0 de thoat chuong trinh): "; 
	std::cin >> o;
	while (!(o >= 0 && o <= 8)) {
		std::cout << "Yeu cau ban nhap khong ton tai, vui long nhap lai: ";
		std::cin >> o;
	}
	return o;
}
void program() {
	unsigned int soluong = 0;
	char file_input[] = "dulieuHH.txt";
	LL list;
	HangHoa data;
	initLL(list);
	soluong = readfromFile(&list, soluong, file_input, data);
	textcolor(14);

	std::cout << "\tDang nhap du lieu tu " << file_input << "...\n";
	textcolor(12);
	unsigned int n = soluong;
	if (!n)
		std::cout << "\t**Nhap du lieu khong thanh cong**\n";
	else
		std::cout << "\t**Nhap du lieu thanh cong**\n";
	
	textcolor(14);
	int option = selection();
	switch (option) {
	case 1: {
		std::cout << "\tSo luong mat hang la ";
		textcolor(14);
		std::cout << soluong;
		textcolor(12);
		std::cout << ".\n";
		textcolor(14);
		std::cout << "\n\tDANH SACH HANG HOA: \n";
		printdata(&list);
	}break;
	case 2: {
		textcolor(10);
		std::cout << "\tHang hoa co don gia > 2000 la ";
		textcolor(11);
		std::cout << demhanghoa(&list);
		textcolor(10);
		std::cout << " mat hang.\n";
	}break;
	case 3: {
		textcolor(10);
		std::cout << "\tTong tien tat ca hang hoa tren la ";
		textcolor(11);
		std::cout << tongtien(&list);
		textcolor(10);
		std::cout << " dong.\n";
	}break;
	case 4: {
		textcolor(10);
		std::cout << "\tDanh sach ten cac hang hoa co so luong < 7 la:\n";
		xuattenhanghoa(&list);
	}break;
	case 5: {
		textcolor(9);
		std::cout << "\tSap xep danh sach hang hoa theo thu tu don gia tang dan.\n";
		sapxepdongia(&list);
		printdata(&list);
	}break;
	case 6: {
		textcolor(9);
		std::cout << "\tSap xep danh sach hang hoa theo thu tu ma hang hoa theo A-Z.\n";
		sapxepmahanghoa(&list);
		printdata(&list);
	}break;
	case 7: {
		std::cout << "\t\tBan muon them mot mat hang vao danh sach, hay nhap cac yeu cau sau: \n";
		themhanghoa(&list, soluong, data, file_input);
		printdata(&list);
	}break;
	case 8: {
		char Loai[] = "Mi";
		xoahanghoa(&list, Loai, soluong, file_input);
		printdata(&list);
	}break;
	default:{
		int i;
		textcolor(7);
		std::cout << "\nThoat chuong trinh trong ";
		for (i = 3; i >= 1; i--) {
			std::cout << i << "s";
			Sleep(1000);
			std::cout << "\b\b";
		}
		exit(0);
	}
		break;
	}
}
int main() {
	textcolor(12);
	title();
	do {
		program();
	} while (true);
	system("pause");
	return 0;
}
