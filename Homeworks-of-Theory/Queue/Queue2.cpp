#include <iostream>
using namespace std;
struct NODE {
	int data;
	NODE* next;
};
struct LIST {
	NODE* head, * tail;
};
struct QUEUE {
	int size;
	int head;
	int tail;
};