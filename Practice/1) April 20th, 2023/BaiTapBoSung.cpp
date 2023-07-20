#include <iostream>
#include <Windows.h>
#include <fstream>
#define MAX 100
void textcolor(int x) {
	HANDLE y = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(y, x);
}

void readFile(int *arr, int &n, char file_input[]) {
	std::ifstream file;
	file.open(file_input);
	if (!file) {
		std::cout << "Error opening specified file" << std::endl;
		system("pause");
		return;
	}
	file >> n;
	for (int i = 0; i < n; i++)
		file >> arr[i];
	file.close();
}
void outputArray(int arr[], int n) {
	std::cout << "So luong phan tu la " << n << std::endl;
	for (int i = 0; i < n; i++)
		std::cout << arr[i] << " ";
	std::cout << '\n';
}

void title() {
	std::cout << "BAI TAP LAM THEM.\n";
	std::cout << "1. Tim kiem x, tra ve vi tri dau tien tim thay.\n";
	std::cout << "2. Sắp xếp số lẻ tăng dần nhưng giá trị khác giữ nguyên vị trí.\n";
	std::cout << "3. Cho 2 mang tang, hay tron thanh mot mang giam dan.\n";
	std::cout << "4. Dua cac so chia het cho 3 ve dau mang.\n";
	std::cout << "5. Dao nguoc mang ban dau.\n\n";
}
int request() {
	int o;
	std::cout << "Ban muon lam yeu cau nao? ";
	std::cin >> o;
	while (!(o >= 0 && o <= 5)) {
		std::cout << "Yeu cau khong hop le, moi ban nhap lai: ";
		std::cin >> o;
	}
	return 0;
}
void program() {
	int arr[MAX], n;
	char file_name[] = "Input.txt";
	readFile(arr, n, file_name);
	outputArray(arr, n);
	title();
	int o = request();
	switch (o)
	{
		case 1: {

		}break;
		case 2: {

		}break;
		case 3: {

		}break;
		case 4: {

		}break;
		case 5: {

		}break;
		default: exit(0);
			break;
	}
}
int main() {
	while (true) {
		textcolor(12);
	program();
	}
	system("pause");
	return 0;
}
