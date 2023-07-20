#include <iostream>
#include <time.h>

struct NODE {
	int info;
	NODE* left;
	NODE* right;
};
struct BinaryTree {
	NODE* root;
};
void initBTree(BinaryTree *bt) {
	bt->root = NULL;
}
NODE* createNODE(int x) {
	NODE* pointer = new NODE;
	if (pointer ==NULL) {
		std::cout << "Khong du bo nho de cap phat node moi" << std::endl;
		return NULL;
	}
	pointer->info = x;
	pointer->left = NULL;
	pointer->right = NULL;
	return pointer;
}
int isEmpty(BinaryTree bt) {
	if (bt.root == NULL) return 0;
	else return 1;
}
void BTreeNLR(NODE* root) {
	if (root==NULL)
		return;
	std::cout << root->info << " ";
	BTreeNLR(root->left);
	BTreeNLR(root->right);
}
void BTreeNRL(NODE* root) {
	if (root == NULL)
		return;
	std::cout << root->info << " ";
	BTreeNRL(root->right);
	BTreeNRL(root->left);
}
void BTreeLNR(NODE* root) {
	if (root==NULL)
		return;
	BTreeLNR(root->left);
	std::cout << root->info << " ";
	BTreeLNR(root->right);
}
NODE* findx_recursive(NODE* root, int x) {
	if (root == NULL) return NULL;
	if (root->info == x) return root;
	else if (root->info > x)
		return findx_recursive(root->left, x);
	else
		return findx_recursive(root->right, x);
}
NODE* findx_nonrecursive(NODE* root, int x) {
	NODE* pointer = root;
	while (pointer!=NULL) {
		if (pointer->info == x)
			return pointer;
		else if (pointer->info > x)
			pointer = pointer->left;
		else
			pointer = pointer->right;
	}
}
int insertNODE_recursive(NODE* root, NODE* pointer) {
	if (pointer == NULL)
		return 0;
	if (root == NULL) {
		root = pointer;
		return 1;
	}
	if (root->info==pointer->info)
		return 0;
	if (pointer->info < root->info)
		insertNODE_recursive(root->left, pointer);
	else
		insertNODE_recursive(root->right, pointer);
	return 1;
}
NODE* findTNodeReplace(NODE*& pointer) {
	NODE* f = pointer;
	NODE* q = pointer->right;
	while (q->left!=NULL) {
		f = q;
		q = q->left;
	}
	pointer->info = q->info;
	if (f == pointer)
		f->right = q->right;
	else
		f->left = q->right;
	return q;
}
int deleteTNODEX(NODE* &root, int x) {
	if (root == NULL)
		return 0;
	if (root->info > x)
		return deleteTNODEX(root->left, x);
	else if (root->info < x)
		return deleteTNODEX(root->right, x);
	else
	{
		NODE* pointer = root;
		if (root->left==NULL)
		{
			root = root->right;
			free(pointer);
		}
		else if (root->right == NULL) {
			root = root->left;
			free(pointer);
		}
		else
		{
			NODE* q = findTNodeReplace(pointer);
			free(pointer);
		}
	}
	return 1;
}
int main() {
	system("cls");
	BinaryTree bt;
	initBTree(bt);
	NODE* pointer;
	int x;
	for (int i = 0; i < 5; i++) {
		srand(time(NULL));
		x = rand() % 99 + 1;
		pointer = createNODE(x);
	}
	
	BTreeLNR(pointer);
	BTreeNLR(pointer);
	BTreeNRL(pointer);
	system("pause");
	return 0;
}