#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h> 


#define SPACE (int)27
//- Cấu trúc môn học và thông tin môn.
#define MAX_MA_MON_HOC 14
#define MAX_TEN_MON_HOC 50
#define MAX_LOAI_MON_HOC 50
#define MAX_HE_DAO_TAO 15
struct ThongTin{
    // Cộng 1 cho \0 ở cuối.
    char ma_mon_hoc[MAX_MA_MON_HOC + 1];
    char ten_mon_hoc[MAX_TEN_MON_HOC + 1];
    char loai_mon_hoc[MAX_LOAI_MON_HOC + 1];
    short int so_tin_chi;
    char he_dao_tao[MAX_HE_DAO_TAO + 1];
};

typedef struct ThongTin InfoType;
struct MonHoc{
    struct Node{
        InfoType data;
        struct Node *left;
        struct Node *right;
    };
    struct Node *root;
};

typedef struct MonHoc BST;
typedef struct Node Node;
//- Các Thao tác:

// Khởi tạo.
void init(BST *T)
{
    T->root = NULL;
}

// Tạo node.
Node *make_node(InfoType x)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if(newNode == NULL){
        printf("Co loi: %s.\n", strerror(errno));
        return NULL;
    }

    newNode->data = x;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Hàm chèn môn học.
Node *insert(Node *root, InfoType x)
{
    if(!root){
        printf("<--Make-->\n");
        return make_node(x);
    }

    int compare = strcmp(root->data.ten_mon_hoc, x.ten_mon_hoc);
    if(compare > 0)
        root->left = insert(root->left, x);
    else if(compare < 0)
        root->right = insert(root->right, x);
    else
        printf("Mon hoc %s da ton tai.\n", x.ten_mon_hoc);
    
    return root;
}

// Xoá 1 node (by Hoàng Tuấn).
Node *min_node(Node *root)
{
    while(root->left != NULL)
        root = root->left;
    return root;
}

Node *delete(Node *root, char *s) {
    // Base-case.
    if(!root)
        return NULL;

    int compare = strcmp(root->data.ten_mon_hoc, s);
    if(compare > 0)
        root->left = delete(root->left, s);
    else if(compare < 0)
        root->right = delete(root->right, s);
    else{
        if(root->left == NULL){
            Node *temp = root->right;
            free(root);
            root = NULL;
            return temp;
        }
        else if(root->right == NULL){
            Node *temp = root->left;
            free(root);
            root = NULL;
            return temp;
        }

        Node *temp = min_node(root->right);
        root->data = temp->data;

        root->right = delete(root->right, temp->data.ten_mon_hoc);
    }
    return root;
}

// Xoá toàn bộ cây (by Hoàng Tuấn).
void delete_tree(Node *root)
{
    if(!root)
        return;

    delete_tree(root->left);
    delete_tree(root->right);
    
    free(root);
    root = NULL;
}

// Cách dòng.
void spacing(int space, FILE *f)
{
    for(int i = SPACE; i < space; i++){
        if(f)
            fprintf(f, "%c", ' ');
        else
            printf(" ");
    }
}

// Đặt dấu gạch theo dòng.
void lining(int space, FILE *f)
{
    int height = (float)space / SPACE;

    for(int i = SPACE; i < space; i++){
        int mid = (int)((float)(space + SPACE) / 2);
        if(f){
            if(i == mid)
                fprintf(f, "%d", height);
            else
                fprintf(f, "%c", '-');
        }
        else{
            if(i == mid)
                printf("%d", height);
            else
                printf("-");
        }
    }

    if(f)
        fprintf(f, "%s", "|\n");
    else 
        printf("|\n");
}

// In dữ liệu của Node.
void display_node_data(InfoType data, int space, FILE *f)
{
    if(!f){
        lining(space, f);
        spacing(space, f);
        printf("|Ma mon hoc: %s\n", data.ma_mon_hoc);
        spacing(space, f);
        printf("|Ten mon hoc: %s\n", data.ten_mon_hoc);
        spacing(space, f);
        printf("|Loai mon hoc: %s\n", data.loai_mon_hoc);   
        spacing(space, f);
        printf("|So tin chi: %hd\n", data.so_tin_chi);
        spacing(space, f);
        printf("|He dao tao: %s\n", data.he_dao_tao);
        lining(space, f);
    }
    else{
        lining(space, f);
        spacing(space, f);
        fprintf(f, "%s%s%c", "|Ma mon hoc: ", data.ma_mon_hoc, '\n');
        spacing(space, f);
        fprintf(f, "%s%s%c", "|Ten mon hoc: ", data.ten_mon_hoc, '\n');
        spacing(space, f);
        fprintf(f, "%s%s%c", "|Loai mon hoc: ", data.loai_mon_hoc, '\n');
        spacing(space, f);
        fprintf(f, "%s%d%c", "|So tin chi: ", data.so_tin_chi, '\n');
        spacing(space, f);
        fprintf(f, "%s%s%c", "|He dao tao: ", data.he_dao_tao, '\n');
        lining(space, f);
    }
}

// Left - Node - Right (by Thuý Diễm).
void LNR(Node *root, int space, FILE *f)
{
    if(!root)
        return;
    
    space += SPACE;
    LNR(root->left, space, f);
    display_node_data(root->data, space, f);
    LNR(root->right, space, f);
}

// Right - Node - Left (by Thuý Diễm).
void RNL(Node *root, int space, FILE *f)
{
    if(!root)
        return;
    
    space += SPACE;
    RNL(root->right, space, f);
    display_node_data(root->data, space, f);
    RNL(root->left, space, f);
}

// Node - Left - Right (by Thuý Diễm).
void NLR(Node *root, int space, FILE *f)
{
    if(!root)
        return;
    
    space += SPACE;
    display_node_data(root->data, space, f);
    NLR(root->left, space, f);
    NLR(root->right, space, f);
}

// Node - Right - Left (by Thuý Diễm).
void NRL(Node *root, int space, FILE *f)
{
    if(!root)
        return;
    
    space += SPACE;
    display_node_data(root->data, space, f);
    NRL(root->right, space, f);
    NRL(root->left, space, f);
}

// Left - Right - Node (by Thuý Diễm).
void LRN(Node *root, int space, FILE *f)
{
    if(!root)
        return;
    
    space += SPACE;
    LRN(root->left, space, f);
    LRN(root->right, space, f);
    display_node_data(root->data, space, f);
}

// Right - Left - Node (by Thuý Diễm).
void RLN(Node *root, int space, FILE *f)
{
    if(!root)
        return;
    
    space += SPACE;
    RLN(root->right, space, f);
    RLN(root->left, space, f);
    display_node_data(root->data, space, f);
}

// Trích chuỗi.
char *str_sub(char *src, int start, int end)
{
    char *dest = (char *)malloc(sizeof(char) * (strlen(src) + 1));
    int length = end - start;

    for(int i = start; i < end && *(src + i) != '\0'; i++){
        *dest = *(src + i);
        dest++;
    }
    // Index cuối cùng sẽ là \0: Null-Terminator.
    *dest = '\0';

    // Mang con trỏ về lại index 0 và return.
    dest = dest - length;
    return dest; 
}

// Kẹp độ dài chuỗi lại.
void clamp_str(int *length, const int max_length)
{
    if(*length > max_length)
        *length = max_length;
}

// Sửa lại string, nếu dữ liệu nhập vào lớn hơn giới hạn.
char *str_fix(char *string, int i)
{
    int newLength = strlen(string);
    switch(i){
        case 0: clamp_str(&newLength, MAX_MA_MON_HOC); break;
        case 1: clamp_str(&newLength, MAX_TEN_MON_HOC); break;
        case 2: clamp_str(&newLength, MAX_LOAI_MON_HOC); break;
        case 4: clamp_str(&newLength, MAX_HE_DAO_TAO); break;
    }
    string = str_sub(string, 0, newLength);
    return string;
}

//- Chống nhập bậy làm crash chương trình.
void flush()
{
    unsigned long long int count = 0;
    char c;
    do{
        c = getchar();
        count++;
    }while(c != '\n' && c != EOF);
    
    if(count > 1)
        printf("---> Da xu li %llu ki tu thua.\n", count);
}

void file_flush(FILE *f, char last)
{
    if(last != '\n'){
        char c;
        do{
            c = fgetc(f);
        }while(c != '\n' && c != EOF);
    }
}

void read_and_clear(char string[], const int size)
{
    if(string[size - 1] == '\0' && (string[size - 2] != '\n' && string[size - 2] != '\0'))
        flush();
}

bool isValid(InfoType x)
{
    if(strcmp(x.ma_mon_hoc, "\0") == 0 || strcmp(x.ma_mon_hoc, "\n") == 0)
        return false;
    if(strcmp(x.ten_mon_hoc, "\0") == 0 || strcmp(x.ten_mon_hoc, "\n") == 0)
        return false;
    if(strcmp(x.loai_mon_hoc, "\0") == 0 || strcmp(x.loai_mon_hoc, "\n") == 0)
        return false;
    if(x.so_tin_chi <= 0 || x.so_tin_chi > 14)
        return false;
    if(strcmp(x.he_dao_tao, "\0") == 0 || strcmp(x.he_dao_tao, "\n") == 0)
        return false;
    
    for(int i = 0; i < strlen(x.he_dao_tao); i++)
        x.he_dao_tao[i] = toupper(x.he_dao_tao[i]);

    if(strcmp(x.he_dao_tao, "CHINH QUY") == 0 || strcmp(x.he_dao_tao, "KHONG CHINH QUY\0") == 0)
        return true;
    return true;                                             
}

// - Tạo string với một kích thước cho trước.
void make_string(char string[], const int size)
{
    fgets(string, size, stdin);
    read_and_clear(string, size);
    string[strcspn(string, "\n")] = '\0';
}

//- Lấy dữ liệu từ Data.txt.
Node *input_file(Node *root)
{
    FILE *f;
    f = fopen("Data.txt", "rt");
    if(f == NULL){
        printf("Co loi: %s.\n", strerror(errno));
        return root;
    }

    // Các dấu ngăn cách delimiters.
    char *delims = "!@#$/\\|~:,.'";
    int length = 256;
    int read_line = 0;
    char string[length];

    while(!feof(f)){
        if(fgets(string, length, f) == NULL){
            // Không có gì để đọc hoặc lỗi IO.
            printf("---> Khong co du lieu hoac loi IO.\n");
            break;
        }
        file_flush(f, string[strcspn(string, "\n")]);
        string[strcspn(string, "\n")] = '\0';
        
        InfoType x;
        int token_index = 0;
        char *token = strtok(string, delims);
        while(token != NULL){
            token = str_fix(token, token_index);
            switch(token_index){
                case 0: strncpy(x.ma_mon_hoc, token, strlen(token) + 1); break;
                case 1: strncpy(x.ten_mon_hoc, token, strlen(token) + 1); break;
                case 2: strncpy(x.loai_mon_hoc, token, strlen(token) + 1); break;
                case 3: x.so_tin_chi = atoi(token); break;
                case 4: strncpy(x.he_dao_tao, token, strlen(token) + 1); break;
                default: printf("---> Rejected %d token_index.\n", token_index);
            }
            token = strtok(NULL, delims);
            token_index++;
        }

        read_line++;
        if(isValid(x))
            root = insert(root, x);
        else
            printf("---> Khong chap nhan du lieu o dong thu %d, xin vui long sua lai.\n", read_line);

        memset(string, '\0', length);
    }
    return root;
}

//- Nhập thủ công.
Node *input_by_hand(Node *root)
{
    InfoType x;
    printf("* Vui long nhap thong tin mon hoc:\n");
    printf("- Ma mon hoc: ");
    make_string(x.ma_mon_hoc, sizeof(x.ma_mon_hoc));

    printf("- Ten mon hoc: ");
    make_string(x.ten_mon_hoc, sizeof(x.ten_mon_hoc));

    printf("- Loai mon hoc: ");
    make_string(x.loai_mon_hoc, sizeof(x.loai_mon_hoc));

    printf("- So tin chi: ");
    scanf("%hd", &x.so_tin_chi);
    flush();

    printf("- He dao tao: ");
    make_string(x.he_dao_tao, sizeof(x.he_dao_tao));

    if(isValid(x))
        root = insert(root, x);
    else
        printf("---> Du lieu vua cung cap khong hop le, xin vui long sua lai.\n");

    return root;
}

//- Main.
void menu()
{
    printf("\t\t\t---CAC THAO TAC TREN CHUONG TRINH---\n");
    printf("\tE. Thoat chuong trinh.\n");
    printf("\tI. Nhap mon hoc.\n");
    printf("\tD. Xoa mon hoc.\n");
    printf("\tS. Tim mon hoc x.\n");
    printf("\tT. Thao tac khac.\n");
    printf("\tP. In cay mon hoc ra man hinh.\n");
    printf("\t\t\t------------------------------------\n");
}

Node *search_theo_mon(Node *root, char *mon_hoc);
Node *search_theo_ma_mon(Node *root, Node **found, char *ma_mon);
int dem_so_luong_mon_theo_loai(Node *root, char *loai_mon_hoc);
void in_mon_hoc_theo_tin_chi(Node *root, short int so_tin_chi, bool *found);
void in_mon_hoc_theo_loai(Node *root, char *loai, bool *found);
int dem_mon_hoc_theo_loai(Node *root, char *loai);
void cap_nhat_loai_mon(Node *root, int *j, char loai_mon[][MAX_LOAI_MON_HOC + 1]);
int tinh_tong_so_tin_chi(Node *root);
int tinh_tong_so_mon_hien_co(Node *root);
short int sub_task()
{
    short int task = -1;
    printf("\t-> ");
    scanf("%hd", &task);
    flush();

    return task;
}

void show(BST T, FILE *f)
{
    printf("\t\t\t====>THAO TAC IN<====\n");
    printf("\t+ 1. Left - Node - Right.\n");
    printf("\t+ 2. Right - Node - Left.\n");
    printf("\t+ 3. Node - Left - Right.\n");
    printf("\t+ 4. Node - Right - Left.\n");
    printf("\t+ 5. Left - Right - Node.\n");
    printf("\t+ 6. Right - Left - Node.\n");

    short int choice_2 = sub_task();
    if(T.root == NULL){
        printf("---> Cay hien khong co du lieu.\n");
        return;
    }
    system("cls");
    switch(choice_2){
        case 1: LNR(T.root, 0, f); break;
        case 2: RNL(T.root, 0, f); break;
        case 3: NLR(T.root, 0, f); break;
        case 4: NRL(T.root, 0, f); break;
        case 5: LRN(T.root, 0, f); break;
        case 6: RLN(T.root, 0, f); break;
        default: printf("---> Yeu cau khong ton tai, quay lai.\n");
    }
}

bool execute(BST *T)
{
    menu();
    char choice;
    printf("> ");
    scanf("%c", &choice);
    flush();

    system("cls");
    switch(toupper(choice)){
            case 'E': return false;
            case 'I':{
                printf("\t\t\t====>THAO TAC NHAP<====\n");
                printf("\t+ 0. Quay lai.\n");
                printf("\t+ 1. Bang file Data.txt.\n");
                printf("\t+ 2. Bang file Tay.\n");

                switch(sub_task()){
                    case 0: return true;
                    case 1: T->root = input_file(T->root); break;
                    case 2: T->root = input_by_hand(T->root); break;
                    default: printf("---> Thao tac nhap nay khong ton tai.\n");
                }
                break;
            }
            case 'D':{
                printf("\t\t\t====>THAO TAC XOA<====\n");
                printf("\t+ 0. Quay lai.\n");
                printf("\t+ 1. Xoa mot mon hoc.\n");
                printf("\t+ 2. Xoa toan bo.\n");
                
                switch(sub_task()){
                    case 0: return true;
                    case 1:{
                        char s[MAX_TEN_MON_HOC + 1];
                        printf("Nhap chinh xac ten mon hoc ban muon xoa: ");
                        make_string(s, sizeof(s));

                        if(search_theo_mon(T->root, s) != NULL){
                            T->root = delete(T->root, s);
                            if(search_theo_mon(T->root, s) == NULL)
                                printf("---> Xoa thanh cong mon hoc %s.\n", s);
                        }
                        else
                            printf("---> Mon hoc %s khong ton tai.\n", s);
                        break;
                    }
                    case 2:{
                        delete_tree(T->root);
                        T->root = NULL;
                        printf("---> Da xoa tat ca cac mon.\n");
                        break;
                    }
                    default: printf("---> Thao tac xoa nay khong ton tai.\n");
                }
                break;
            }
            case 'S':{
                printf("\t\t\t====>THAO TAC TIM<====\n");
                printf("\t+ 0. Quay lai.\n");
                printf("\t+ 1. Theo mon.\n");
                printf("\t+ 2. Theo ma mon hoc.\n");

                switch(sub_task()){
                    case 0: return true;
                    case 1:{
                        char s[MAX_TEN_MON_HOC + 1];
                        printf("Nhap ten mon hoc ban muon tim: ");
                        make_string(s, sizeof(s));
                        
                        Node *found = search_theo_mon(T->root, s);
                        if(found != NULL){
                            printf("Tim thay, sau day la thong tin cua mon hoc %s:\n", found->data.ten_mon_hoc);
                            printf("- Ma mon hoc: %s.\n", found->data.ma_mon_hoc);
                            printf("- Loai mon hoc: %s.\n", found->data.loai_mon_hoc);
                            printf("- So tin chi: %hd.\n", found->data.so_tin_chi);
                            printf("- He dao tao: %s.\n", found->data.he_dao_tao);
                        }
                        else
                            printf("---> Khong tim thay mon hoc %s.\n", s);
                        break;
                    }
                    case 2:{
                        char s[MAX_MA_MON_HOC + 1];
                        printf("Nhap ma mon hoc ban muon tim: ");
                        make_string(s, sizeof(s));
                        
                        Node *found = NULL;
                        search_theo_ma_mon(T->root, &found, s);
                        if(found != NULL){
                            printf("Tim thay! Sau day la thong tin cua mon hoc %s:\n", found->data.ten_mon_hoc);
                            printf("- Ma mon hoc: %s.\n", found->data.ma_mon_hoc);
                            printf("- Loai mon hoc: %s.\n", found->data.loai_mon_hoc);
                            printf("- So tin chi: %hd.\n", found->data.so_tin_chi);
                            printf("- He dao tao: %s.\n", found->data.he_dao_tao);
                        }
                        else
                            printf("---> Khong tim thay mon hoc co ma mon %s.\n", s);             
                        break;
                    }
                    default: printf("---> Thao tac tim nay khong ton tai.\n");
                }
                break;
            }
            case 'T':{
                printf("\t\t\t====>CAC THAO TAC CON<====\n");
                printf("\t+ 0. Quay lai.\n");
                printf("\t+ 1. Thong ke mon hoc theo so tin chi.\n");
                printf("\t+ 2. Thong ke mon hoc theo loai.\n");
                printf("\t+ 3. Dem so luong mon hoc theo tung loai.\n");
                printf("\t+ 4. Tinh tong so tin chi cac mon.\n");
                printf("\t+ 5. Tinh tong cac mon hien co.\n");
                
                switch(sub_task()){
                    case 0: return true;
                    case 1:{
                        int n;
                        int limit = 5;
                        bool found = false;

                        printf("- So bang thong ke: ");
                        do{
                            scanf("%d", &n);
                            flush();
                            if(n <= 0)
                                printf("---> Khong hop le(> 0), nhap lai: ");
                            if(n > limit)
                                printf("---> Qua gioi han(<= 5), nhap lai: ");
                        }while(n <= 0 || n > limit);
                        short int so_tin_chi[n];

                        for(int i = 0; i < n; i++){
                            printf("-> ");
                            scanf("%hd", &so_tin_chi[i]);
                            flush();
                        }

                        for(int i = 0; i < n; i++){
                            found = false;
                            printf("******************MON HOC %d TIN CHI******************\n", so_tin_chi[i]);
                            in_mon_hoc_theo_tin_chi(T->root, so_tin_chi[i], &found);
                            if(found == false)
                                printf("---> Khong co mon hoc %hd tin chi.\n", so_tin_chi[i]);
                        }
                        break;
                    }
                    case 2:{
                        int n;
                        int limit = 5;
                        bool found = false;

                        printf("- So bang thong ke: ");
                        do{
                            scanf("%d", &n);
                            flush();
                            if(n <= 0)
                                printf("---> Khong hop le(> 0), nhap lai: ");
                            if(n > limit)
                                printf("---> Qua gioi han(<= 5), nhap lai: ");
                        }while(n <= 0 || n > limit);
                        char loai_mon[n][MAX_LOAI_MON_HOC];

                        for(int i = 0; i < n; i++){
                            printf("-> ");
                            make_string(loai_mon[i], sizeof(loai_mon[i]));
                        }

                        for(int i = 0; i < n; i++){
                            found = false;
                            printf("******************MON HOC THUOC LOAI %s******************\n", loai_mon[i]);
                            in_mon_hoc_theo_loai(T->root, loai_mon[i], &found);
                            if(found == false)
                                printf("---> Khong co mon hoc thuoc loai %s.\n", loai_mon[i]);
                        }
                        break;
                    }
                    case 3:{
                        int so_mon = tinh_tong_so_mon_hien_co(T->root);
                        if(so_mon == 0){
                            printf("---> Hien dang khong co mon hoc nao de dem.\n");
                            return true;
                        }
                        int j = 0;
                        char loai_mon[so_mon][MAX_LOAI_MON_HOC + 1];
                        cap_nhat_loai_mon(T->root, &j, loai_mon);

                        for(int i = 0; i < j; i++)
                            printf("+ %s co: %d mon.\n", loai_mon[i], dem_mon_hoc_theo_loai(T->root, loai_mon[i]));
                        break;
                    }
                    case 4: printf("Tong so tin chi: %d.\n", tinh_tong_so_tin_chi(T->root)); break;
                    case 5: printf("Tong so mon hoc: %d.\n", tinh_tong_so_mon_hien_co(T->root)); break;
                    default: printf("---> Thao tac con nay khong ton tai.\n");
                } /*Sub-switch*/
                break;
            }
            case 'P':{
                printf("\t\t\t====>KIEU IN<====\n");
                printf("\t+ 0. Quay lai.\n");
                printf("\t+ 1. In tren man hinh Console.\n");
                printf("\t+ 2. In ra file.\n");
                switch(sub_task()){
                    case 0: return true;
                    case 1: show(*T, NULL); break;
                    case 2:{
                        FILE *f;
                        f = fopen("output.txt", "w");
                        show(*T, f);
                        fclose(f);
                        break;
                    }
                }
                break;
            }
            default: printf("---> Yeu cau khong ton tai, vui long chon lai.\n");
        } /*Main switch*/
    return true;
}

int main(void)
{
    BST T1;
    init(&T1);
    if(T1.root != NULL){
        printf("---> Khoi tao cay khong thanh cong!\n");
        exit(0);
    }
    printf("---> Khoi tao cay thanh cong!\n");

    bool process = true;
    while(process){
        process = execute(&T1);
    }

    printf("---> Thoat chuong trinh thanh cong.\n");
    return EXIT_SUCCESS;
}


// - Các tác vụ con:
// Tìm kiếm theo môn học (by Hồ Kiến Thức).
Node *search_theo_mon(Node *root, char *mon_hoc)
{   
    if(!root)
        return NULL;
    int compare = strcmp(root->data.ten_mon_hoc, mon_hoc);

    if(compare == 0)
        return root;
    else if(compare > 0)
        return search_theo_mon(root->left, mon_hoc);
    else
        return search_theo_mon(root->right, mon_hoc);
}

// Tìm kiếm theo mã môn học (by Hồ Kiến Thức).
Node *search_theo_ma_mon(Node *root, Node **found, char *ma_mon)
{
    if(!root)
        return *found;

    search_theo_ma_mon(root->left, found, ma_mon);
    search_theo_ma_mon(root->right, found, ma_mon);
    if(strcmp(root->data.ma_mon_hoc, ma_mon) == 0)
        *found = root;
}

int dem_so_luong_mon_theo_loai(Node *root, char *loai_mon_hoc)
{
    if(!root)
        return 0;
    
    int leftC = dem_so_luong_mon_theo_loai(root->left, loai_mon_hoc);
    int rightC = dem_so_luong_mon_theo_loai(root->right, loai_mon_hoc);

    if(strcmp(root->data.loai_mon_hoc, loai_mon_hoc) == 0)
        return leftC + rightC + 1;
    return leftC + rightC;
}

void in_mon_hoc_theo_tin_chi(Node *root, short int so_tin_chi, bool *found)
{
    if(!root)
        return;
    in_mon_hoc_theo_tin_chi(root->left, so_tin_chi, found);
    in_mon_hoc_theo_tin_chi(root->right, so_tin_chi, found);

    if(root->data.so_tin_chi == so_tin_chi){
        *found = true;
        printf("+ %s.\n", root->data.ten_mon_hoc);
    }
}

void in_mon_hoc_theo_loai(Node *root, char *loai, bool *found)
{
    if(!root)
        return;
    in_mon_hoc_theo_loai(root->left, loai, found);
    in_mon_hoc_theo_loai(root->right, loai, found);

    if(strcmp(root->data.loai_mon_hoc, loai) == 0){
        *found = true;
        printf("+ %s.\n", root->data.ten_mon_hoc);
    }
}

int dem_mon_hoc_theo_loai(Node *root, char *loai)
{
    if(!root)
        return 0;
    int leftC = dem_mon_hoc_theo_loai(root->left, loai);
    int rightC = dem_mon_hoc_theo_loai(root->right, loai);

    if(strcmp(root->data.loai_mon_hoc, loai) == 0)
        return leftC + rightC + 1;
    return leftC + rightC;
}

bool check_exist_loai_mon(int j, char loai_mon[][MAX_LOAI_MON_HOC + 1], char *x)
{
    for(int i = 0; i <= j; i++){
        if(strcmp(loai_mon[i], x) == 0)
            return true;
    }
    return false;
}

void cap_nhat_loai_mon(Node *root, int *j, char loai_mon[][MAX_LOAI_MON_HOC + 1])
{
    if(!root)
        return;
    
    cap_nhat_loai_mon(root->left, j, loai_mon);
    cap_nhat_loai_mon(root->right, j, loai_mon);

    if(!check_exist_loai_mon(*j, loai_mon, root->data.loai_mon_hoc)){
        strcpy(loai_mon[*j], root->data.loai_mon_hoc);
        *j = *j + 1;
    }
}

int tinh_tong_so_tin_chi(Node *root)
{
    if(!root)
        return 0;

    int leftC = tinh_tong_so_tin_chi(root->left);
    int rightC = tinh_tong_so_tin_chi(root->right);

    return leftC + rightC + root->data.so_tin_chi;
}

int tinh_tong_so_mon_hien_co(Node *root)
{
    if(!root)
        return 0;

    int leftC = tinh_tong_so_mon_hien_co(root->left);
    int rightC = tinh_tong_so_mon_hien_co(root->right);

    return leftC + rightC + 1;
}