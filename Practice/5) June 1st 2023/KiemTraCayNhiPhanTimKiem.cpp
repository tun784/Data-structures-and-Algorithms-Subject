#include <iostream>
using namespace std;

// Định nghĩa cấu trúc của một nút trong cây
struct NODE {
    int data;
    NODE* left;
    NODE* right;
};
typedef struct BinarySearchTree{
    NODE* root;
}BST;
void initBST(BST& bst) {
    bst.root = NULL;
}
// Hàm để tạo một nút mới
NODE* createNode(int value) {
    NODE* newNode = new NODE;
    newNode->data = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Hàm để thêm một nút vào cây
int insertNode(NODE *&root, int value) {
    if (root == NULL) {
        root = createNode(value);
        return 1;
    }
    if (value == root->data) {
        cout << "Gia tri da ton tai.\n";
        return 0;
    }
    if (value < root->data) {
        insertNode(root->left, value);
    }
    else {
        insertNode(root->right, value);
    }
}
void traverseNLR(NODE* node) {
    if (node == NULL)
        return;
    cout << node->data << " ";
    traverseNLR(node->left);
    traverseNLR(node->right);
}
// Hàm để tính tổng các phần tử của cây con bên phải của gốc
int sumRightSubtree(NODE* root) {
    if (root == nullptr || root->right == nullptr) {
        return 0;
    }
    return root->right->data + sumRightSubtree(root->right->left) + sumRightSubtree(root->right->right);
}

// Hàm để tìm phần tử lớn nhất trong cây
int findMax(NODE* root) {
    if (root == nullptr) {
        cout << "Empty tree.\n"<< endl;
        return INT_MIN;
    }
    if (root->right == nullptr) {
        return root->data;
    }
    return findMax(root->right);
}

// Hàm để đếm số lượng số chẵn trong cây
int countEvenNumbers(NODE* root) {
    if (root == nullptr) {
        return 0;
    }
    int count = 0;
    if (root->data % 2 == 0) {
        count++;
    }
    count += countEvenNumbers(root->left);
    count += countEvenNumbers(root->right);
    return count;
}
int title() {
    int choice;
    cout << "1. Them gia tri vao cay." << endl;
    cout << "2. Tinh tong cac phan tu cua cay con ben phai cua goc." << endl;
    cout << "3. Xuat phan tu lon nhat trong cay." << endl;
    cout << "4. Dem so luong so chan trong cay." << endl;
    cout << "0. Thoat" << endl;
    cout << "Lua chon cua ban: ";
    cin >> choice;
    while (!(choice >= 0 && choice <= 4)) {
        cout << "Ban da nhap sai yeu cau, vui long nhap lai: ";
        cin >> choice;
    }
    return choice;
}
int main() {
    BST bst;
    initBST(bst);
    int choice;
    int arr[] = { 5,3,7,2,4,1,8,6,9 };
    int size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < size; i++) {
        insertNode(bst.root, arr[i]);
    }
    
    do {
        choice = title();
        switch (choice) {
        case 0:
            exit(0);
            break;
        case 1: {
            cout << "Da nhap du lieu tu mang A thanh cong.\n"; 
            traverseNLR(bst.root);
            cout << endl;
        }break;
        case 2:
            cout << "Tong cac phan tu cua cay con ben phai cua goc: " << sumRightSubtree(bst.root) << endl;
            break;
        case 3:
            cout << "Phan tu lon nhat trong cay: " << findMax(bst.root) << endl;
            break;
        case 4:
            cout << "So luong so chan trong cay: " << countEvenNumbers(bst.root) << endl;
            break;
        default:
            exit(0);
            break;
        }

    } while (choice != 0);

    return 0;
}
