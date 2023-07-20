#include <iostream>
struct DATE {
	int day, month, year;
};
struct SinhVien {
	std::string name = NULL;
	DATE age = { 0,0,0 };
	std::string tinhtrang = NULL;
};
void tinhtrang(SinhVien *sinhvien) {
	sinhvien->tinhtrang = "Co bo";
}
int main() {
	system("cls");
	SinhVien sv[3] = {
		{"Kieu Nga", {24,01,2004} ,"Doc Than"},
		{"B", {24,11,2004} ,"Co bo"},
		{"C", {11,06,2004} ,"Doc Than"}
	};
	SinhVien *sinhvien = nullptr;
	int s = sizeof(sv) / sizeof(SinhVien);
	for (int i = 0; i < s; i++) {
		sinhvien = &sv[i];
		std::cout << sinhvien->name << std::endl;
		std::cout << (*sinhvien).age.day << "/" << sinhvien->age.month << "/" << sinhvien->age.year << std::endl;
		std::cout << sinhvien->tinhtrang << std::endl;
		tinhtrang(sinhvien);
		std::cout << sinhvien->tinhtrang << std::endl;
	}
	system("pause");
	return 0;
}