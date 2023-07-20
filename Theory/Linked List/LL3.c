/*This program creates a linked list with three nodesand allows the user to enter data into each node.*/
/*It includes functions to create a new node, print a node, insert a node at the head, insert a node at the tail, and enter data into each node.*/
/*The main function creates the initial linked list, prints it, calls the enter_data function to allow the user to enter data into each node, and then prints the updated linked list.*/
#include <stdio.h>
#include <stdlib.h>

// Define the node structure
typedef struct node {
	int data;
	struct node* next;
}node;

// Function to create a new node
node* create_node(int x) {
	node* new_node = (node*)malloc(sizeof(node));
	new_node->data = x;
	new_node->next = NULL;
	return new_node;
}

// Function to print a node
void print_node(node* p) {
	printf("%d ", p->data);
}

// Function to insert a node at the head
node* insert_head(node* head, int data) {
	node* p = create_node(data);
	p->next = head;
	return p;
}

// Function to insert a node at the tail
void insert_tail(node* head, int data) {
	node* new_node = create_node(data);
	node* current = head;
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = new_node;
}

// Function to enter data into each node
void enter_data(node* head) {
	node* current = head;
	while (current != NULL) {
		printf("Enter data for node %d: ", current->data);
		scanf_s("%d", &(current->data));
		current = current->next;
	}
}

int main() {
	// Create the initial linked list
	node* head = create_node(1);
	head->next = create_node(2);
	head->next->next = create_node(3);

	// Print the initial linked list
	printf("Initial linked list: ");
	node* current = head;
	while (current != NULL) {
		print_node(current);
		current = current->next;
	}
	printf("\n");

	// Enter data into each node
	enter_data(head);

	// Print the updated linked list
	printf("Updated linked list: ");
	current = head;
	while (current != NULL) {
		print_node(current);
		current = current->next;
	}
	printf("\n");

	return 0;
}