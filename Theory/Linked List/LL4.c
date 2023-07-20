#include <stdio.h>
#include <stdlib.h>

// Define the structure for eachnode in the linked list
typedef struct node {
    int data;
     struct node* next;
}node;

// Function to create a newnode and return a pointer to it
node* create_node(int x) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = x;
    new_node->next = NULL;
    return new_node;
}

// Function to print the data in anode
void print_node(node* n) {
    printf("%d ", n->data);
}

// Function to insert a node at the head of the linked list
void insert_head(node** head_ref, int data) {
    node* new_node = create_node(data);
    new_node->next = *head_ref;
    *head_ref = new_node;
}

// Function to insert a node at the tail of the linked list
void insert_tail(node** head_ref, int data) {
    node* new_node = create_node(data);
    node* tail = *head_ref;
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = new_node;
}

int main() {
    node* head = NULL; // Initialize the head pointer to NULL
    int data, choice;
    do {
        printf("\nEnter the data: ");
        scanf_s("%d", &data);
        printf("\n1. Insert at head");
        printf("\n2. Insert at tail");
        printf("\n3. Exit");
        printf("\nEnter your choice: ");
        scanf_s("%d", &choice);
        switch (choice) {
        case 1: insert_head(&head, data);
            break;
        case 2: insert_tail(&head, data);
            break;
        case 3: exit(0);
        default: printf("\nInvalid choice");
            break;
        }
        printf("\nLinked list: ");
        node* temp = head;
        while (temp != NULL) {
            print_node(temp);
            temp = temp->next;
        }
    } while (choice != 3);
    return 0;
}