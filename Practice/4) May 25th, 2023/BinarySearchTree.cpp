#include <iostream>
#include <math.h>
#include <fstream>

struct NODE {
	int data;
	NODE* left;
	NODE* right;
};
struct BTree {
	NODE* Root;
};
void initTree(BTree& BT) {
	BT.Root = NULL;
}
NODE* createNode(int x) {
	NODE* pointer = new NODE;
	if (!pointer)
		return NULL;
	pointer->data = x;
	pointer->left = NULL;
	pointer->right = NULL;
	return pointer;
}
void insertNode(BTree* root, int x) {
	NODE* pointer = createNode(x);
	if (root->Root->left = NULL) {
		
	}
}

void readfile(BTree* root, char file_input[]) {
	std::ifstream file;
	file.open(file_input);

}
int main() {

	system("pause");
	return 0;
}
