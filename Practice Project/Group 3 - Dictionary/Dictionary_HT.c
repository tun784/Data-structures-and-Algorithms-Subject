#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 26  // Buckets
#define MAX 50   // Số từ vựng
#define TenFile "dictionary.txt"

void xoaXuongDong(char s[]) {
    int len = strlen(s);
    if (s[len - 1] == '\n')
        s[len - 1] = '\0';
}

typedef struct TuDien {
    char word[MAX];
    char meaning[MAX];
}TuDien;

typedef struct NODE {
    TuDien key;
    struct NODE* Next;
}NODE;

NODE* Bucket[SIZE];

void init() {
    for (int i = 0; i < SIZE; i++) {
        Bucket[i] = NULL;
    }
}

NODE* makeNode(TuDien td) {
    NODE* p = (NODE*)malloc(sizeof(NODE));
    if (!p) return NULL;
    p->key = td;
    p->Next = NULL;
    return p;
}

// Chen cuoi bucket
void insertNode(NODE* p, int b) {
    if (Bucket[b] == NULL) {
        Bucket[b] = p;
    }
    else {
        NODE* q = Bucket[b];
        while (q->Next != NULL)
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
void DocFile(TuDien *a, int *n) {
    FILE* f = fopen(TenFile, "r");
    if (!f) {
        printf("\n Loi doc file !");
        return;
    }
    fscanf(f, "%d\n", &*n);
    for (int i = 0; i < *n; i++) {
        fscanf(f, "%[^#]#%[^\n] ", &a[i].word, &a[i].meaning);
        int b = hashFunc(a[i].word[0]);
        NODE* p = makeNode(a[i]);
        insertNode(p, b);
    }
    fclose(f);
}

// Xuat tu vung TA
void xuatTuVung(TuDien a[]) {
    printf("\n\t============XUAT TU VUNG TIENG ANH============================\n");
    for (int b = 0; b < MAX; b++)
    {
        printf("\t|%5d. %s\n",b + 1, a[b].word);
    }
    printf("\t|");
    printf("\n\t==============================================================\n");

}
// Xuat tu dien doc tu file
void xuatTuDien(TuDien a[], int n) {
    printf("\t So luong tu: %d \n", n);
    printf("\n\t==========TU DIEN ANH VIET====================================\n");
    printf("\t|\n");
    for (int i = 0; i < n; i++) {
        printf("\t|%5d. %s:%s\n",i +1, a[i].word, a[i].meaning);
    }
    printf("\t|");
    printf("\n\t==============================================================\n");
}

// Tra nghia cua tu vung Anh - Viet
void traTuDien(char s[]) {
    int b = hashFunc(s[0]);
    NODE* p = Bucket[b];
    
    while (p != NULL && strcmp(_strupr(p->key.word), _strupr(s)) != 0)
        p = p->Next;
    if (p == NULL)
        printf("\n\n\tKhong tim thay \"%s\" trong tu dien", s);
    else {
        printf("\n\t==============================================================\n");
        printf("\t||");
        printf("\n\t|| Nghia cua tu \"%s\": %s", s, p->key.meaning);
        printf("\n\t||");
        printf("\n\t==============================================================\n");
    }

}

void menu() {
    printf("\t\t\t========================================================\n");
    printf("\t\t\t*         ------------/MENU/-------------------        *\n");
    printf("\t\t\t*    0. Thoat chuong trinh                             *\n");
    printf("\t\t\t*    1. Xuat tu dien Anh - Viet                        *\n");
    printf("\t\t\t*    2. Xuat tu vung Tieng Anh                         *\n");
    printf("\t\t\t*    3. Tra tu trong tu dien                           *\n");
    printf("\t\t\t========================================================\n");
}
void process() {
    TuDien a[MAX];
    int n = 0, choose;
    menu();
    init();
    DocFile(a, &n);  
    do { 
        printf("\n\t Nhap lua chon: "); scanf("%d", &choose); getchar();
        
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
            char s[MAX];
            printf("\n\t=> Nhap tu vung can tra: "); fgets(s, MAX, stdin); xoaXuongDong(s);   
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
