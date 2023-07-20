#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <math.h>
#include <string>
#include <fstream>
#include <Windows.h>
#define MAX 100
//Hàm xoá dấu ENTER
void flush_stdin() {
	int c;
	while (((c = getchar()) != '\n' || '\0') && c != EOF);
}
//Hàm xoá dấu ENTER trong file
void flush_file(std::ifstream& f) {
	char c;
	while (f.get(c) && c != '\n' && c != std::ifstream::traits_type::eof());
}
//Hàm đổi màu chữ
void textcolor(int x) {
	HANDLE y = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(y, x);
}
//Bai 1
void readfromFile(int* array, int& number, char file_input[]) {
	std::ifstream file;
	file.open(file_input);
	if (!file) {
		std::cout << "Error opening specified file";
		system("pause");
		return;
	}
	file >> number;
	for (int i = 0; i < number; i++)
		file >> array[i];
	file.close();
}
void outputArray(int array[], int number) {
	std::cout << number << std::endl;
	for (int i = 0; i < number; i++)
		std::cout << array[i] << " ";
	std::cout << std::endl;
}
void swap(int* x, int* y) {
	int t = *x;
	*x = *y;
	*y = t;
}
// Merge sort implementation
void merge(int* arr, int l, int m, int r) {
	int n1 = m - l + 1;
	int n2 = r - m;
	// Create temporary arrays
	int* L = new int[n1];
	int* R = new int[n2]; //Instead of: int L[n1], R[n2];
	
	// Copy data to temporary arrays
	for (int i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];
	// Merge the temporary arrays
	int i = 0, j = 0, k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	// Copy the remaining elements of L[] and R[]
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}
void mergeSort(int* arr, int l, int r) {
	
	if (l >= r) {
		// Base case: array has only one element or is empty
		return;
	}
	// Find the middle point to divide the array into two halves
	int m = l + (r - l) / 2;
	// Recursively sort first and second halves
	mergeSort(arr, l, m);
	mergeSort(arr, m + 1, r);
	// Recursively sort first and second halves
	merge(arr, l, m, r);
}
//Quick sort implementation
int partition(int* arr, int left, int right) {
	int pivot = arr[right]; // choose pivot as rightmost element
	int i = left - 1; // initialize i to left-1

	for (int j = left; j < right; j++) {
		if (arr[j] < pivot) { // if current element is less than pivot
			i++; // increment i
			swap(&arr[i], &arr[j]); // swap arr[i] and arr[j]
		}
	}
	// swap arr[i+1] and arr[right], so that the pivot element is in its correct position
	swap(&arr[i + 1], &arr[right]);

	return i;
}
void quickSort(int* arr, int left, int right) {
	if (left >= right) // base case
		return;
	int pi = partition(arr, left, right);

	// recursively sort the subarrays to the left and right of the pivot
	quickSort(arr, left, pi);
	quickSort(arr, pi + 2, right);
}
// Heap sort implementation
void heapify(int* arr, int n, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	// If left child is larger than root
	if (left < n && arr[left] > arr[largest])
		largest = left;
	// If right child is larger than largest so far
	if (right < n && arr[right] > arr[largest])
		largest = right;
	// If largest is not root
	if (largest != i) {
		swap(&arr[i], &arr[largest]);
		// Recursively heapify the affected sub-tree
		heapify(arr, n, largest);
	}
}
void heapSort(int* arr, int n) {
	// Build heap (rearrange array)
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);
	// One by one extract an element from heap
	for (int i = n - 1; i >= 0; i--) {
		swap(&arr[0], &arr[i]);
		// Call max heapify on the reduced heap
		heapify(arr, i, 0);
	}
}
//void sortArray(int* array, int n) {
//	int temp;
//
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < n - i - 1; j++)
//		{
//			if (array[j] > array[j + 1])
//			{
//				temp = array[j];
//				array[j] = array[j + 1];
//				array[j + 1] = temp;
//			}
//		}
//	}
//}
void writeArrayToFile(int array[], int n, char file_output[]) {
	std::ofstream output(file_output);
	output << "Mang co so luong phan tu la " << n << " sau khi sap xep la : \n";
	for (int i = 0; i < n; i++) {
		output << array[i] << " ";
	}
	output.close();
}
void clearFile(char filename[]) {
	std::ofstream ofs;
	ofs.open(filename, std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

int sort_selection() {
	int o;
	std::cout << "Cac thuat toan\n(1) Merge Sort\n(2) Quick Sort\n(3) Heap Sort\nBan muon sap xep bang thuat toan nao: ";
	std::cin >> o;
	while (!(o>=1 && o<=3))
	{
		std::cout << "Khong co thuat toan nay, vui long ban chon lai: ";
		std::cin >> o;
	}
	return o;
}
void session_1() {
	int array[MAX];
	int number = 0;
	char file_input[] = "Input.txt";
	char file_output[] = "Output.txt";
	readfromFile(array, number, file_input);
	outputArray(array, number);
	textcolor(14);
	int o = sort_selection();

	switch (o) {
		case 1: {
			mergeSort(array, 0, number - 1);

			writeArrayToFile(array, number, file_output);
			char file_input[] = "Output.txt";
			textcolor(10);
			outputArray(array, number);
			readfromFile(array, number, file_input);
		}break;
		case 2: {
			quickSort(array, 0, number - 1);

			writeArrayToFile(array, number, file_output);
			char file_input[] = "Output.txt";
			textcolor(10);
			outputArray(array, number);
			readfromFile(array, number, file_input);
		}break;
		case 3: {
			heapSort(array, number);

			writeArrayToFile(array, number, file_output);
			char file_input[] = "Output.txt";
			textcolor(10);
			outputArray(array, number);
			readfromFile(array, number, file_input);
		}break;
		default: {
			std::cout << "ERROR..." << std::endl;
			exit(1);
		} break;
	}
}
//Bai 2
struct Zoo {
	//std::string MaDongVat;
	std::string TenGoi;
	std::string Loai;
	std::string ThucAn;
	unsigned char tuoi;
	char GioiTinh[10];
	char MaDongVat[20];
};
//Nhập danh sách các con vật từ file vào chương trình
void inputZoo(Zoo* Animal, int* n, std::string file_input) {
	std::ifstream file;
	file.open(file_input);
	if (!file) {
		std::cout << "Error opening the file ";
		return;
	}
	file >> *n;
	std::cout << "So luong con vat: " << *n;
	for (int i = 0; i < *n; i++) {
		flush_file(file);
		file >> Animal[i].MaDongVat;
		flush_file(file);
		getline(file, Animal[i].TenGoi);
		getline(file, Animal[i].Loai);
		file >> Animal[i].GioiTinh;
		flush_file(file);
		getline(file, Animal[i].ThucAn);
		file >> Animal[i].tuoi;
	}
	file.close();
}
//Xuất danh sách các con vật ra màn hình
void outputZoo(Zoo Animal[], int n) {
	std::cout << "Xuat danh sach cac con vat trong so thu: \n";
	for (int i = 0; i < n; i++) { 
		std::cout << "Con thu " << i + 1 << std::endl;
		std::cout << "Ma Dong Vat: " << Animal[i].MaDongVat << std::endl;
		std::cout << "Ten Con Vat: " << Animal[i].TenGoi << std::endl;
		std::cout << "Loai: " << Animal[i].Loai << std::endl;
		std::cout << "Gioi tinh (Duc/Cai): " << Animal[i].GioiTinh << std::endl;
		std::cout << "Thuc an chu yeu (Thit/Co): " << Animal[i].ThucAn << std::endl;
		std::cout << "Tuoi: " << Animal[i].tuoi << std::endl;
		std::cout << std::endl;
	}
}
void printZoo(Zoo Animal[], int i) {
	std::cout << "\nCon thu " << i + 1 << std::endl;
	std::cout << "Ma Dong Vat: " << Animal[i].MaDongVat << std::endl;
	std::cout << "Ten Con Vat: " << Animal[i].TenGoi << std::endl;
	std::cout << "Loai: " << Animal[i].Loai << std::endl;
	std::cout << "Gioi tinh (Duc/Cai): " << Animal[i].GioiTinh << std::endl;
	std::cout << "Thuc an chu yeu (Thit/Co): " << Animal[i].ThucAn << std::endl;
	std::cout << "Tuoi: " << Animal[i].tuoi << std::endl;
}
void if_DVanthit(Zoo Animal[], int n) {
	for (int i = 0; i < n; i++)
		//if (Animal[i].ThucAn == std::string("Thit") || Animal[i].ThucAn == std::string("thit"))
		if (Animal[i].ThucAn.compare("Thit") == 0)
			printZoo(Animal, i);
}
int count_DVbosat(Zoo Animal[], int n) {
	unsigned int sum = 0;
	for (int i = 0; i < n; i++)
		//if (Animal[i].Loai == "bo sat" || Animal[i].Loai == "Bo sat")
		if (Animal[i].Loai.compare("Bo sat") == 0)
			sum++;
	return sum;
}
int count_DVduoinuoc(Zoo Animal[], int n) {
	unsigned int sum = 0;
	for (int i = 0; i < n; i++)
		if (Animal[i].Loai == std::string("duoi nuoc") || Animal[i].Loai == std::string("Duoi nuoc"))
			sum++;
	return sum;
}
void session_2() {
	Zoo Animal[MAX];
		textcolor(7);
			std::cout << "Cau truc co kich thuoc la " << sizeof(Zoo) << " va " << sizeof(Animal[0]);
				std::cout << " ngoai ra kieu du lieu char co kich thuoc la " << sizeof(Animal->MaDongVat) << '\n';
		textcolor(9);
	int number = 0;
	std::string file_input = "Zoo.txt";
	inputZoo(Animal, &number, file_input);
	std::cout << '\n';
	std::cout << "Danh sach cac loai dong vat an thit la: \n";
	if_DVanthit(Animal, number);
	std::cout << '\n';
	std::cout << "So luong dong vat loai bo sat la "; 
		textcolor(10); 
	std::cout << count_DVbosat(Animal, number); 
		textcolor(9); 
		std::cout <<". " << std::endl;
	std::cout << "Thong ke co "; 
		textcolor(10); 
	std::cout << count_DVduoinuoc(Animal, number); 
		textcolor(9); 
	std::cout << " loai duoi nuoc.\n";
	std::cout << std::endl;
	textcolor(14);
	//outputZoo(Animal, number);
}
int select_session() {
	int o;
	std::cout << "Ban muon chon bai nao (hoac nhap so 0 de thoat chuong trinh) ? ";
	std::cin >> o;
	while (!(o >= 0 && o <= 2)) {
		std::cout << "Ban nhap khong hop le, vui long nhap lai: ";
		std::cin >> o;
	}
	return o;
}
void program() {
	textcolor(12);
	int select = select_session();
	
	switch (select) {
	case 0: {
		char o;
		std::cout << "Truoc khi thoat chuong trinh, ban muon xoa file ";
		textcolor(10); std::cout << "Output.txt"; textcolor(12);
		std::cout << " o bai 1 khong ? (Y/N): ";
		std::cin >> o;
		switch (o) {
			case 'y':
			case 'Y': {
				char file_name[] = "Output.txt";
				clearFile(file_name);
				std::cout << "Da xoa tat ca du lieu trong file";
				Sleep(1000);
				exit(0);
			}
			break;
			case 'n':
			case 'N': {
				exit(0);
			}
			break;
			default: {
				std::cout << "ERROR\n";
				Sleep(1000);
				exit(0); 
			}
			break;
		}
		exit(0); 
	}break;
		case 1: {
			textcolor(11);
			session_1();
		}break;
		case 2: {
			textcolor(9);
			session_2();
		}break;
		default:
			break;
	}
}
int main() {
	while (true)
		
		program();
	system("pause");
	return 0;
}
