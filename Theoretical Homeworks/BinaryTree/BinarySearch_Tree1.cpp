#include <iostream>

struct NODE {
    int data;
    NODE* left;
    NODE* right;
};
struct BinaryTree {
    NODE* root;
};
void initTree(BinaryTree* tree) {
    tree->root = NULL;
}

NODE* createNode(int data) {
    NODE* node = new NODE;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}
void insertNode(BinaryTree* tree, int data) {
    NODE* node = createNode(data);
    if (tree->root == NULL) {
        tree->root = node;
    }
    else {
        NODE* current = tree->root;
        NODE* parent;
        while (true)
        {
            parent = current;
            if (data < current->data) {
                current = current->left;
                if (current == NULL) {
                    parent->left = node;
                    break;
                }
            }
            else {
                current = current->right;
                if (current == NULL) {
                    parent->right = node;
                    break;
                }
            }
        }
    }
}

NODE* findNode(BinaryTree* tree, int data) {
    NODE* current = tree->root;
    while (current->data != data)
    {
        if (data < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
        if (current == NULL) {
            return NULL;
        }
    }
    return current;
}
NODE* getSuccessor(NODE* node) {
    NODE* successorParent = node;
    NODE* successor = node;
    NODE* current = node->right;
    while (current != NULL) {
        successorParent = successor;
        successor = current;
        current = current->left;
    }
    if (successor != node->right) {
        successorParent->left = successor->right;
        successor->right = node->right;
    }
    return successor;
}
void deleteNode(BinaryTree* tree, int data) {
    NODE* current = tree->root;
    NODE* parent = tree->root;
    bool isLeft = true;
    while (current->data != data) {
        parent = current;
        if (data < current->data) {
            isLeft = true;
            current = current->left;
        }
        else {
            isLeft = false;
            current = current->right;
        }
        if (current == NULL) {
            return;
        }
    }
    if (current->left == NULL && current->right == NULL) {
        if (current == tree->root) {
            tree->root = NULL;
        }
        else if (isLeft) {
            parent->left = NULL;
        }
        else {
            parent->right = NULL;
        }
    }
    else if (current->right == NULL) {
        if (current == tree->root) {
            tree->root = current->left;
        }
        else if (isLeft) {
            parent->left = current->left;
        }
        else {
            parent->right = current->left;
        }
    }
    else if (current->left == NULL) {
        if (current == tree->root) {
            tree->root = current->right;
        }
        else if (isLeft) {
            parent->left = current->right;
        }
        else {
            parent->right = current->right;
        }
    }
    else {
        NODE* successor = getSuccessor(current);
        if (current == tree->root) {
            tree->root = successor;
        }
        else if (isLeft) {
            parent->left = successor;
        }
        else {
            parent->right = successor;
        }
        successor->left = current->left;
    }
    delete current;
}
//Preorder: NLR
void traverseNLR(NODE* node)
{
    if (node != NULL)
    {
        std::cout << node->data << " ";
        traverseNLR(node->left);
        traverseNLR(node->right);
    }
}
//Postorder: NRL
void traverseNRL(NODE* node)
{
    if (node != NULL)
    {
        traverseNRL(node->left);
        traverseNRL(node->right);
        std::cout << node->data << " ";
    }
}
//Inorder: LNR
void traverseLNR(NODE* node)
{
    if (node != NULL)
    {
        traverseLNR(node->left);
        std::cout << node->data << " ";
        traverseLNR(node->right);
    }
}
//Inorder: RNL
void traverseRNL(NODE* node)
{
    if (node != NULL)
    {
        traverseRNL(node->right);
        std::cout << node->data << " ";
        traverseRNL(node->left);
    }
}
//Preorder: LRN
void traverseLRN(NODE* node)
{
    if (node != NULL)
    {
        traverseLRN(node->left);
        traverseLRN(node->right);
        std::cout << node->data << " ";
    }
}
//Postorder: RLN
void traverseRLN(NODE* node)
{
    if (node != NULL)
    {
        traverseRLN(node->right);
        traverseRLN(node->left);
        std::cout << node->data << " ";
    }
}

int main()
{
    BinaryTree tree;
    initTree(&tree);
    int choice;
    int data;
    while (true)
    {
        std::cout << "1. Insert Node" << std::endl;
        std::cout << "2. Find Node" << std::endl;
        std::cout << "3. Delete Node" << std::endl;
        std::cout << "4. Traverse NLR" << std::endl;
        std::cout << "5. Traverse NRL" << std::endl;
        std::cout << "6. Traverse LNR" << std::endl;
        std::cout << "7. Traverse RNL" << std::endl;
        std::cout << "8. Traverse LRN" << std::endl;
        std::cout << "9. Traverse RLN" << std::endl;
        std::cout << "10. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            std::cout << "Enter data: ";
            std::cin >> data;
            insertNode(&tree, data);
            break;
        case 2:
            std::cout << "Enter data: ";
            std::cin >> data;
            if (findNode(&tree, data) != NULL)
            {
                std::cout << "Node found!" << std::endl;
            }
            else
            {
                std::cout << "Node not found!" << std::endl;
            }
            break;
        case 3:
            std::cout << "Enter data: ";
            std::cin >> data;
            deleteNode(&tree, data);
            break;
        case 4:
            traverseNLR(tree.root);
            std::cout << std::endl;
            break;
        case 5:
            traverseNRL(tree.root);
            std::cout << std::endl;
            break;
        case 6:
            traverseLNR(tree.root);
            std::cout << std::endl;
            break;
        case 7:
            traverseRNL(tree.root);
            std::cout << std::endl;
            break;
        case 8:
            traverseLRN(tree.root);
            std::cout << std::endl;
            break;
        case 9:
            traverseRLN(tree.root);
            std::cout << std::endl;
            break;
        case 10:
            exit(0);
            break;
        default:
            std::cout << "Invalid choice!" << std::endl;
            break;
        }
    }
    return 0;
}