#include <iostream>
using namespace std;
#define MAX_SIZE 101 
int A[MAX_SIZE];
int front = -1;
int rear = -1;

// Xuất Queue
void Print() {
    int i;
    if (front == -1) {
        cout << "Queue is Empty" << endl;
        return;
    }
    for (i = front; i <= rear; i++)
        cout << A[i] << " ";
    cout << endl;
}
// Kiểm tra Queue rỗng 
bool IsEmpty() {
    return (front == -1 && rear == -1);
}
// Kiểm tra Queue đầy  
bool IsFull() {
    return (rear + 1) % MAX_SIZE == front ? true : false;
}
// Thêm một phần tử vào cuối Queue  
void Enqueue(int x) {
    cout << "Enqueuing " << x << endl;
    if (IsFull()) {
        cout << "Error: Queue is Full" << endl;
        return;
    }
    if (IsEmpty()) {
        front = rear = 0;
    }
    else {
        rear = (rear + 1) % MAX_SIZE;
    }
    A[rear] = x;
    cout << "Enqueued " << x << endl;
    Print();
    return;
}
// Lấy một phần tử ở đầu ra khỏi Queue  
int Dequeue() {
    cout << "Dequeuing" << endl;
    int x;
    if (IsEmpty()) {
        cout << "Error: Queue is Empty" << endl;
        return INT_MIN;
    }
    else if (front == rear) {
        x = A[front];
        front = -1;
        rear = -1;
    }
    else {
        x = A[front];
        front = (front + 1) % MAX_SIZE;
    }
    cout << "Dequeued " << x << endl;
    Print();
    return x;
}
// Xem phần tử ở đầu của Queue    
int Front() {
    if (front == -1) {
        cout << "Error: cannot return front from empty queue" << endl;
        return -1;
    }
    return A[front];
}
// Xem phần tử ở cuối của Queue    
int Rear() {
    if (rear == -1) {
        cout << "Error: cannot return rear from empty queue" << endl;
        return -1;
    }
    return A[rear];
}

// Kiểu dữ liệu một nút trong Queue 
struct Node {
	int data;
	Node* next;
};

// Thêm phần tử vào Queue 
void Enqueue(Node** rear, int x)
{
	// Tạo một nút
	Node* temp = new Node;
	temp->data = x;
	temp->next = NULL;

	// Nếu Queue rỗng, trước đầu là rear 
	if (*rear == NULL) {
		*rear = temp;
		return;
	}

	// Ngược lại, thêm nút temp vào cuối Queue 
	(*rear)->next = temp;
	*rear = temp;
}

// Lấy phần tử từ đầu Queue ra 
void Dequeue(Node** front)
{
	Node* temp = *front;

	// Nếu Queue rỗng 
	if (*front == NULL)
		return;

	// Nếu Queue có một phần tử 
	if ((*front)->next == NULL) {
		*front = NULL;
		free(temp);
		return;
	}

	// Nếu Queue có hơn một phần tử, lấy phần tử đầu tiên 
	*front = (*front)->next;
	free(temp);
}

// In Queue 
void PrintQueue(Node* front)
{
	if (front == NULL) {
		cout << "Queue rong" << endl;
		return;
	}
	cout << "Queue : ";
	while (front != NULL) {
		cout << front->data << " --> " << endl;
		front = front->next;
	}
	cout << "NULL" << endl;
}

// Trả về phần tử ở đầu Queue 
int Front(Node* front){
	if (front == NULL)
		return -1;
	return front->data;
}

// Trả về phần tử ở cuối Queue 
int Rear(struct Node* rear){
	if (rear == NULL)
		return -1;
	return rear->data;
}

// Xác định xem Queue đầy hay không 
int IsFull(Node* rear){
	return 0;
}

// Xác định xem Queue rỗng hay không 
int IsEmpty(Node* front){
	return (front == NULL);
}
// Hàm chính 
int main() {
    cout << "Array: " << endl;
    // Cài đặt queue bằng mảng
    Enqueue(2);
    Enqueue(4);
    Enqueue(6);
    Dequeue();
    Enqueue(8);
    cout << "Front item is " << Front() << endl;
    cout << "Rear item is " << Rear() << endl;
    // Cài đặt queue bằng danh sách liên kết
    cout << endl;
    cout << "Linked List: " << endl;
    Node* front = NULL, * rear = NULL;
    // Queue rỗng ban đầu 
    cout << "Queue rong? " << IsEmpty(front) << endl;
    // Thêm phần tử 
    Enqueue(&rear, 10);
    Enqueue(&rear, 20);
    Enqueue(&rear, 30);
    Enqueue(&rear, 40);
    Enqueue(&rear, 50);
    // Xuất Queue
    PrintQueue(front);
    // Phần tử ở đầu Queue 
    cout << "Phan tu o dau Queue : " << Front(front) << endl;
    // Phần tử ở cuối Queue 
    cout << "Phan tu o cuoi Queue : " << Rear(rear) << endl;
    // Phần tử lấy ra khỏi Queue 
    Dequeue(&front);
    Dequeue(&front);
    // Queue sau khi lấy phần tử ra 
    PrintQueue(front);
    system("pause");
    return 0;
}