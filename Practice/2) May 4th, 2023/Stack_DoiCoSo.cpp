#include <conio.h>
#include <stdio.h>

typedef int ItemType;
struct StackNode
{
	ItemType Info;
	StackNode* Next;
};
struct Stack
{
	StackNode* Top;
};

//*************************************************
StackNode* createStackNode(ItemType x)
{
	StackNode* p = new StackNode;
	if(p == NULL)
	{
		printf("Không đủ bộ nhớ để cấp phát!");
		getch();
		return NULL;
	}
	p->Info = x;
	p->Next = NULL;
	return p;
}
//*************************************************
void initStack(Stack &s)
{ //Initialize Stack
	s.Top = NULL;
}
//*************************************************
int isEmpty(Stack s)
{//Tra ve 1 neu rong, nguoc lai tra ve 0
	return (s.Top == NULL);
}
//*************************************************
int push(Stack &s, StackNode* p)
{
	if(p == NULL)
		return 0; //Không thực hiện được
	if(isEmpty(s) == 1)
		s.Top = p;
	else
	{
		p->Next = s.Top;
		s.Top = p;
	}
	return 1; //Thực hiện thành công
}
//*************************************************
int pop(Stack &s, ItemType &x)
{
	if(isEmpty(s) == 1) //Stack rỗng
		return 0; //Không thực hiện được
	StackNode* p = s.Top;
	s.Top = s.Top->Next;
	x = p->Info; //Lấy thông tin của nút ở đỉnh Stack
	delete p; //Hủy nút do p trỏ đến
	return 1; //Thực hiện thành công
}
//*************************************************
void stack_DoiCoSo(int n, int a)
{//Đổi từ hệ 10 sang một hệ số a (a>=2 và a<=9).
	int sodu, x;
	StackNode* p;
	Stack stack;
	initStack(stack);
	while(n != 0)
	{
		sodu = n%a;
		n /= a;
		p = createStackNode(sodu);
		push(stack, p);
	}
	printf("\nKet qua doi tu he 10 sang he %d la: ", a);
	while(1)
	{
		if(pop(stack, x) == 0)
			break;
		switch (x)
		{
			case 10: printf("A"); break;
			case 11: printf("B"); break;
			case 12: printf("C"); break;
			case 13: printf("D"); break;
			case 14: printf("E"); break;
			case 15: printf("F"); break;
			default: printf("%d", x);
		}		
	}
}

//*************************************************
void main()
{
	int n, heso, sodu;
	ItemType x;
	do
	{
		printf("Hay nhap mot so he 10: ");
		scanf ("%d", &n);
	}while(n <= 0);
	do
	{
		printf("Hay nhap co so muon doi: ");
		scanf ("%d", &heso);
	}while(heso <= 0);
	stack_DoiCoSo(n, heso);
	getch();
}
