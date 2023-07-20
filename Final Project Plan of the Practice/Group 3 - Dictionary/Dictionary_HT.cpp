#include <iostream>
#include <cstring>
#include <ctype.h>
#include <iomanip>
#include <fstream>
#include <limits>

#define SIZE 26  // Buckets
#define MAX 50   // Số từ vựng
#define TenFile "dictionary.txt"

void xoaXuongDong(std::string& s) {
    int len = s.length();
    if (s[len - 1] == '\n')
        s[len - 1] = '\0';
}

struct TuDien {
    std::string word;
    std::string meaning;
};

struct NODE {
    TuDien key;
    NODE* Next;
};

NODE* Bucket[SIZE];

void init() {
    for (int i = 0; i < SIZE; i++) {
        Bucket[i] = nullptr;
    }
}

NODE* makeNode(TuDien td) {
    NODE* p = new NODE;
    if (!p) return nullptr;
    p->key = td;
    p->Next = nullptr;
    return p;
}

// Chen cuoi bucket
void insertNode(NODE* p, int b) {
    if (Bucket[b] == nullptr) {
        Bucket[b] = p;
    }
    else {
        NODE* q = Bucket[b];
        while (q->Next != nullptr)
            q = q->Next;
        q->Next = p;
    }
}
// Ham bam
int hashFunc(char c) {
    if (isalpha(c)) {
        return tolower(c) - 'a';
    }
    // Trường hợp không phải chữ cái, trả về giá trị không hợp lệ (ví dụ: -1)
    return -1;
}
// Doc file 50 tu vung
void DocFile(TuDien* a, int* n) {
    std::ifstream file;
    file.open(TenFile);
    if (!file) {
        std::cout << "\n Loi doc file !";
        return;
    }

    file >> *n;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 0; i < *n; i++) {
        std::getline(file, a[i].word, '#');
        std::getline(file, a[i].meaning);
    }

    file.close();
}

// Xuat tu vung TA
void xuatTuVung(TuDien a[]) {
    std::cout << "\n\t============XUAT TU VUNG TIENG ANH============================\n";
    for (int b = 0; b < MAX; b++)
    {
        std::cout << "\t|" << b + 1 << ". " << a[b].word << "\n";
    }
    std::cout << "\t|";
    std::cout << "\n\t==============================================================\n";
}
// Xuat tu dien doc tu file
void xuatTuDien(TuDien a[], int n) {
    int s1 = 2;
    int s2 = 25;
    std::cout << "\t So luong tu: " << n << "\n";
    std::cout << "\n\t==========TU DIEN ANH VIET====================================\n";
    std::cout << "\t|\n";
    for (int i = 0; i < n; i++) {
        std::cout << "|" << std::left << std::setw(s1) << i + 1 << ". " << std::setw(s2) << a[i].word << ":" << a[i].meaning << "\n";
    }
    std::cout << "\t|";
    std::cout << "\n\t==============================================================\n";
}

// Tra nghia cua tu vung Anh - Viet
void traTuDien(std::string s) {
    int b = hashFunc(s[0]);
    NODE* p = Bucket[b];

    while (p != nullptr && _stricmp(p->key.word.c_str(), s.c_str()) != 0)
        p = p->Next;
    if (p == nullptr)
        std::cout << "\n\n\tKhong tim thay \"" << s << "\" trong tu dien";
    else {
        std::cout << "\n\t==============================================================\n";
        std::cout << "\t||";
        std::cout << "\n\t|| Nghia cua tu \"" << s << "\": " << p->key.meaning;
        std::cout << "\n\t||";
        std::cout << "\n\t==============================================================\n";
    }

}

void menu() {
    std::cout << "\t\t\t========================================================\n";
    std::cout << "\t\t\t*         ------------/MENU/-------------------        *\n";
    std::cout << "\t\t\t*    0. Thoat chuong trinh                             *\n";
    std::cout << "\t\t\t*    1. Xuat tu dien Anh - Viet                        *\n";
    std::cout << "\t\t\t*    2. Xuat tu vung Tieng Anh                         *\n";
    std::cout << "\t\t\t*    3. Tra tu trong tu dien                           *\n";
    std::cout << "\t\t\t========================================================\n";
}
void process() {
    TuDien a[MAX];
    int n = 0, choose;
    menu();
    init();
    DocFile(a, &n);
    do {
        std::cout << "\n\t Nhap lua chon: "; std::cin >> choose; std::cin.ignore();

        switch (choose) {
        case 1: {
            xuatTuDien(a, n);
            break;
        }
        case 2:
        {
            xuatTuVung(a);
            break;
        }
        case 3: {
            std::string s;
            std::cout << ("\n\t=> Nhap tu vung can tra: "); std::getline(std::cin, s);
            xoaXuongDong(s);
            traTuDien(s);
            break;
        }
        default:
            break;
        }
    } while (choose != 0);
}

int main() {
    process();
    return 0;
}
