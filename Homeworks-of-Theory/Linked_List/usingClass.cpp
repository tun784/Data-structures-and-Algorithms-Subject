#include <iostream>
#include <cmath>
using namespace std;

// A node class for linked list
class Node {
public:
    int data; // The data stored in the node
    Node* next; // The pointer to the next node

    // A constructor that takes a data value
    Node(int value) {
        data = value;
        next = NULL;
    }
};

// A linked list class
class LinkedList {
public:
    Node* head; // The pointer to the head of the list
    Node* tail; // The pointer to the tail of the list

    // A constructor that creates an empty list
    LinkedList() {
        head = NULL;
        tail = NULL;
    }

    // A method that inserts a node at the end of the list
    void insert(int val) {
        Node* newNode = new Node(val); // Create a new node with the given value
        if (head == NULL) { // If the list is empty, set the head and tail to the new node
            head = newNode;
            tail = newNode;
        }
        else { // Otherwise, append the new node to the tail and update the tail pointer
            tail->next = newNode;
            tail = newNode;
        }
    }

    // A method that removes a node from the beginning of the list and returns its data value
    int remove() {
        if (head == NULL) { // If the list is empty, return -1 as an error code
            return -1;
        }
        else { // Otherwise, store the data value of the head node and delete it
            int val = head->data; // Store the data value of the head node
            Node* temp = head; // Store a temporary pointer to the head node
            head = head->next; // Move the head pointer to the next node
            delete temp; // Delete the old head node
            return val; // Return the data value of the deleted node
        }
    }

    // A method that prints all the data values in the list
    void print() {
        Node* curr = head; // Start from the head of the list
        while (curr != NULL) { // Loop until reaching the end of the list
            cout << curr->data << " "; // Print the data value of the current node
            curr = curr->next; // Move to the next node
        }
        cout << endl; // Print a newline at the end
    }
};

// A stack class that uses linked list as its underlying data structure
class Stack {
public:
    LinkedList list; // The linked list that stores the stack elements

    // A constructor that creates an empty stack
    Stack() {
        list = LinkedList(); // Initialize an empty linked list
    }

    // A method that pushes a value onto the top of the stack
    void push(int val) {
        list.insert(val); // Insert a new node at the end of the linked list the given value 
        //(this becomes the top of the stack)
    }

    // A method that pops a value from the top of the stackand returns it
        int pop() {
        return list.remove();
        // Remove a node from the beginning of the linked listand return its data value(this is the top of the stack)
        }

    // A method that prints all the values in the stack from top to bottom
        void print() {
        list.print();
        // Print all the data values in the linked list(this corresponds to the order of the stack elements)
        }
};

// A queue class that uses linked list as its underlying data structure 
class Queue {
public:
    LinkedList list;
    // The linked list that stores the queue elements
        // A constructor that creates an empty queue 
    Queue() {
        list = LinkedList();
        // Initialize an empty linked list 
    }

    // A method that enqueues a value at the back of the queue
    void enqueue(int val) {
        list.insert(val);
    }
    // Insert a new node at the end of the linked list with the given value(this becomes the back of the queue)
// A method that dequeues a value from the front of the queueand returns it
    int dequeue() {
        LinkedList list;
        return list.remove();
        // Remove a node from the beginning of the linked listand return its data value(this is the front of the queue)
    }
    // A method that prints all the values in the queue from front to back
    void print() {
        LinkedList list;
        list.print();
        // Print all the data values in the linked list(this corresponds to the order of the queue elements)
    }
};
// A main function that tests the stack and queue classes
int main() {
    // Create a stack object
    Stack s;
    // Push some values onto the stack
    s.push(10);
    s.push(20);
    s.push(30);
    // Print the stack contents
    cout << "Stack: ";
    s.print();
    // Pop some values from the stack
    cout << "Popped: " << s.pop() << endl;
    cout << "Popped: " << s.pop() << endl;
    // Print the stack contents again
    cout << "Stack: ";
    s.print();

    // Create a queue object
    Queue q;
    // Enqueue some values into the queue
    q.enqueue(40);
    q.enqueue(50);
    q.enqueue(60);
    // Print the queue contents
    cout << "Queue: ";
    q.print();
    // Dequeue some values from the queue
    cout << "Dequeued: " << q.dequeue() << endl;
    cout << "Dequeued: " << q.dequeue() << endl;
    // Print the queue contents again
    cout << "Queue: ";
    q.print();
    system("pause");
    return 0;
}