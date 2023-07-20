#include <conio.h>
#include <stdio.h>
#include <string.h>

typedef char ItemType;
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
void stack_DaoChuoi(char *chuoi)
{
	ItemType ch;
	StackNode* p;
	Stack stack;
	initStack(stack);
	int len = strlen(chuoi);
	for(int i = 0; i < len; i++)
	{
		p = createStackNode(chuoi[i]);
		push(stack, p);
	}
	printf("\nChuoi dao nguoc la: ");
	while(1)
	{		
		if(pop(stack, ch) == 0)
			break;
		printf("%c", ch);
	}
}

//*************************************************
void main()
{
	char chuoi[100];	
	printf("Hay nhap mot chuoi bieu thuc chua dau ngoac: ");
	gets(chuoi);
	stack_DaoChuoi(chuoi);
	getch();
}
