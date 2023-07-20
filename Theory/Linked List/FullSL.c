#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

#define NOT_FOUND INT_MIN

typedef struct{
    int data;
    void *link;
}Node;

typedef struct{
    Node *head;
    Node *tail;
}List;

void printNode(List l);
void init_list(List *l);
void menu(char type, List *l)
{
    switch(type){
        case '\0':{
            printf("\n---Singly Linked List operations---\n");
            printf("* Press I for INSERTION\n");
            printf("* Press D for DELETION\n");
            printf("* Press P to print NODE.\n");
            printf("* Press T to do a task.\n");
            printf("* Press R to reset LIST.\n");
            printf("* Press Q to QUIT.\n");
            break;
        }
        case 'I':{
            printf("\t0. Exit.\n");
            printf("\t1. Insert node at beginning.\n");
            printf("\t2. Insert node at K position.\n");
            printf("\t3. Insert node at end of the list.\n");
            break;
        }
        case 'D':{
            printf("\t0. Exit.\n");
            printf("\t1. Delete node at beginning.\n");
            printf("\t2. Delete node at K position.\n");
            printf("\t3. Delete node at end of the list.\n");
            break;
        }
        case 'P':{
            printf("- Your list: ");
            printNode(*l);
            break;
        }
        case 'T':{
            printf("Task 1: Sorting singly linked List.\n");
            printf("Task 2: Counting node(s).\n");
            printf("Task 3: Finding sum of all existing node(s).\n");
            printf("Task 4: Printing request.\n");
            printf("Task 5: Finding x.\n");
            printf("Task 6: Counting how many x exists in the list.\n");
            printf("Task 7: Finding request.\n");
            printf("Task 8: Deleting max or min.\n");
            break;
        }
        case 'R':{
            printf("Reset...\n");
            init_list(l);
            break;
        }
        case 'Q': exit(0);
        default:{
            printf("%c does not exist!\n", type);
            return;
        }
    }
}

Node *make_node(int x)
{
    Node *newNode = NULL;
    newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL){
        perror("Error");
        printf("Exit code %d.\n", errno);
        exit(errno);
    }
    newNode->data = x;
    return newNode;
}

void add_beginning(List *l, int value)
{
    Node *newNode = make_node(value);
    if(l->head == NULL){
        newNode->link = l->tail;
        l->head = l->tail = newNode;
    }
    else{
        newNode->link = l->head;
        l->head = newNode;
    }
}

void add_mid(List *l, int value, int k)
{
    Node *prev = NULL;
    Node *curr = l->head;
    if(curr == NULL){
        printf("List is empty, can't insert.\n");
        return;
    }
    while(curr != NULL && k != 0){
        prev = curr;
        curr = curr->link;
        k--;
    }

    if(k >= 1 || k < 0){
        printf("Unable to insert at the given position.\n");
        return;
    }
    Node *newNode = make_node(value);
    prev->link = newNode;
    newNode->link = curr;
    l->tail = newNode;
}

void add_end(List *l, int value)
{
    Node *newNode = make_node(value);
    if(l->head == NULL){
        l->head = l->tail = newNode;
        return;
    }
    newNode->link = NULL;
    l->tail->link = newNode;
    l->tail = newNode;   
}

void del_beginning(List *l)
{
    if(l->head == NULL){
        printf("List is empty, can't delete\n");
        return;
    }

    if(l->tail == l->head)
        l->tail = NULL;
    Node *temp = l->head;
    l->head = l->head->link;
    free(temp);
}

void del_mid(List *l, int k)
{
    Node *prev = NULL;
    Node *curr = l->head;
    if(curr == NULL){
        printf("List is empty, can't delete\n");
        return;
    }
    while(curr->link != NULL && k != 1){
        prev = curr;
        curr = curr->link;
        k--;
    }
    if(k > 1 || k < 0){
        printf("Unable to delete at the given position.\n");
        return;
    }
    else if(prev == NULL){
        l->head = l->head->link;
        free(curr);
        return;
    }
    else if(curr->link == NULL){
        prev->link = NULL;
        l->tail = prev; 
        free(curr);
    }
    else{
        prev->link = curr->link;
        free(curr);
    }
}

void del_end(List *l)
{
    Node *prev = NULL;
    Node *curr = l->head;
    if(curr == NULL){
        printf("List is empty, can't delete\n");
        return;
    }
    while(curr->link != NULL){
        prev = curr;
        curr = curr->link;
    }

    if(prev == NULL){
        l->head = NULL;
        l->tail = NULL;
        free(curr);
        return;
    }
    l->tail = prev;
    prev->link = NULL;
    free(curr);
}

void printNode(List l)
{
    Node *temp = l.head;
    if(temp == NULL)
        printf("Empty-");
    while(temp != NULL){
        printf("%d [%p]->", temp->data, temp);
        temp = temp->link;
    }
    printf("NULL\n");
    printf("Head: %p\n", l.head);
    printf("Tail: %p\n", l.tail);
}

void sort(List *l, int i);
int count_node(List l);
int sum_node(List l);
void print_request(List l, int i);
Node *find_x(List l, int x);
int count_x(List l, int x);
void finding_request(List l, int i, int *found_num, bool *found, bool *list_empty);
void deleting_request(List *l, int i);
bool operate(List *l)
{
    void (*menu_ptr)(char, List *) = &menu;
    (*menu_ptr)('\0', l);
    char typeOf;
    printf("-> ");
    scanf("%c", &typeOf);
    typeOf = toupper(typeOf);
    (*menu_ptr)(typeOf, l);

    int numOf;
    switch(typeOf){
        case 'I':
        printf("\\-> ");
        scanf("%d", &numOf);
        switch(numOf){
            case 1:{
                int x;
                printf("What number should I insert?\n-> ");
                scanf("%d", &x);
                add_beginning(l, x);
                return true;
            }
            case 2:{
                int x, pos;
                printf("What number should I insert?\n-> ");
                scanf("%d", &x);
                printf("Where? Position(int): ");
                scanf("%d", &pos);
                add_mid(l, x, pos);
                return true;
            }
            case 3:{
                int x;
                printf("What number should I insert?\n-> ");
                scanf("%d", &x);
                add_end(l, x);
                return true;
            }
            default:{
                printf("%d operation does not exist!\n", numOf);
                return true;
            }
        }
        break;

        case 'D':
        printf("\\-> ");
        scanf("%d", &numOf);
        switch(numOf){
            case 1:{
                del_beginning(l);
                return true;
            }
            case 2:{
                int pos;
                printf("Where? Position(int): ");
                scanf("%d", &pos);
                del_mid(l, pos);
                return true;
            }
            case 3:{
                del_end(l);
                return true;
            }
            default:{
                printf("%d operation does not exist!\n", numOf);
                return true;
            }
        }
        break;

        case 'T':
        printf("\\-> ");
        scanf("%d", &numOf);
        switch(numOf){
            case 1:{
                int choose;
                printf("\t- Press 1 for Increasing Sort.\n");
                printf("\t- Press 2 for Decreasing Sort.\n");
                printf("* Which sort do you want me to provide?\n-> ");
                do{
                    scanf("%d", &choose);
                    if(choose < 1 || choose > 2)
                        printf("Your request seems wrong, please try again.\n-> ");
                }while(choose < 1 || choose > 2);
                sort(l, choose - 1);
                return true;
            }
            case 2:{
                printf("You're having %d node(s)", count_node(*l));
                return true;
            }
            case 3:{
                if(l->head == NULL)
                    printf("List is empty.\n");
                else
                    printf("Sum of all nodes is %d\n", sum_node(*l));
                return true;
            }
            case 4:{
                int choose;

                printf("\t- Press 1 for Printing odd node(s).\n");
                printf("\t- Press 2 for Printing even node(s).\n");
                printf("\t- Press 3 for Printing node at odd position.\n");
                printf("\t- Press 4 for Printing node at even position.\n");
                printf("* Which one do you want me to provide?\n-> ");
                do{
                    scanf("%d", &choose);
                    if(choose < 1 || choose > 4)
                        printf("Your request seems wrong, please try again.\n-> ");
                }while(choose < 1 || choose > 4);
                print_request(*l, choose - 1);
                return true;
            }
            case 5:{
                int x;
                printf("What data do you want me to find in the list?\n-> ");
                scanf("%d", &x);

                Node *found = find_x(*l, x);
                if(found == NULL){
                    printf("Your result: Not found.\n");
                    printf("* Your list could be empty or x does not exist.\n");
                }
                else
                    printf("Your result: %d at [%p].\n", x, found);
                
                return true;
            }
            case 6:{
                int x, number_found = 0;
                printf("What data do you want me to find in the list?\n-> ");
                scanf("%d", &x);
                
                int found = count_x(*l, x);
                if(found == 0){
                    printf("Your result: Not found.\n");
                    printf("* Your list could be empty or x does not exist.\n");
                }
                else
                    printf("%d x is existing in the list.\n", found);
                
                return true;
            }
            case 7:{
                bool list_empty = true, found = false;
                int choose, found_num;
                printf("\t- Press 1 to find max.\n");
                printf("\t- Press 2 to find min.\n");
                printf("\t- Press 3 to find odd max.\n");
                printf("\t- Press 4 to find even min.\n");
                printf("* Which one do you want me to provide?\n-> ");
                do{
                    scanf("%d", &choose);
                    if(choose < 1 || choose > 4)
                        printf("Your request seems wrong, please try again.\n-> ");
                }while(choose < 1 || choose > 4);
                finding_request(*l, choose - 1, &found_num, &found, &list_empty);
                if(list_empty == true)
                    printf("* Your list is empty.\n");
                
                if(found == true)
                    printf("Your result: %d.\n", found_num);
                else
                    printf("Your result: Not found.\n");
                
                return true;
            }
            case 8:{
                int choose;
                printf("\t- Press 1 to delete max.\n");
                printf("\t- Press 2 to delete min.\n");
                printf("* Which one do you want me to provide?\n-> ");
                do{
                    scanf("%d", &choose);
                    if(choose < 1 || choose > 2)
                        printf("Your request seems wrong, please try again.\n-> ");
                }while(choose < 1 || choose > 2);
                deleting_request(l, choose - 1);
                return true;
            }
            default:{
                printf("%d operation does not exist!\n", numOf);
                return true;
            }
        }
        break;
    }
}

void init_list(List *l)
{
    l->head = NULL;
    l->tail = NULL;
}

int main(void)
{
    List l1;
    init_list(&l1);
    bool set_process = true;
    while(set_process){
        set_process = operate(&l1);
        getchar();
    }

    return 0;
}

void swap(Node *x, Node *y)
{
    int temp = x->data;
    x->data = y->data;
    y->data = temp;
}

void increasing_sort(List *l)
{
    Node *curr = l->head;
    Node *index = NULL;

    if(curr == NULL){
        printf("List is empty, can't sort.\n");
        return;
    }
    
    while(curr != NULL){
        index = curr->link;

        while(index != NULL){
            if(curr->data > index->data)
                swap(curr, index);
            index = index->link;
        }
        curr = curr->link;
    }
}

void decreasing_sort(List *l)
{
    Node *curr = l->head;
    Node *index = NULL;

    if(curr == NULL){
        printf("List is empty, can't sort.\n");
        return;
    }
    
    while(curr != NULL){
        index = curr->link;

        while(index != NULL){
            if(curr->data < index->data)
                swap(curr, index);
            index = index->link;
        }
        curr = curr->link;
    }
}

void sort(List *l, int i)
{
    void (*choose[])(List *) = {increasing_sort, decreasing_sort};
    (*choose[i])(l);
}

int count_node(List l)
{
    int count = 0;
    while(l.head != NULL){
        count++;
        l.head = l.head->link;
    }
    return count;
}

int sum_node(List l)
{
    int sum = 0;
    while(l.head != NULL){
        sum += l.head->data;
        l.head = l.head->link;
    }
    return sum;
}

void print_odd(List l)
{
    Node *temp = l.head;
    bool found = false;
    printf("Your result: ");
    while(l.head != NULL){
        if(l.head->data % 2 != 0){
            found = true;
            printf("%d ", l.head->data);
        }
        l.head = l.head->link;
    }
    if(found == false || temp == NULL)
        printf("No nodes were found.\n");
}

void print_even(List l)
{
    Node *temp = l.head;
    bool found = false;
    printf("Your result: ");
    while(l.head != NULL){
        if(l.head->data % 2 == 0){
            found =
            printf("%d ", l.head->data);
        }
        l.head = l.head->link;
    }
    if(found == false || temp == NULL)
        printf("No nodes were found.\n");
}

void print_node_at_oddPos(List l)
{
    Node *temp = l.head;
    bool found = false;
    int i = 0;
    printf("Your result: ");
    while(l.head != NULL){
        if(i % 2 != 0){
            found = true;
            printf("%d ", l.head->data);
        }
        l.head = l.head->link;
        i++;
    }
    if(found == false || temp == NULL)
        printf("No nodes were found.\n");
}

void print_node_at_evenPos(List l)
{
    Node *temp = l.head;
    bool found = false;
    int i = 0;
    printf("Your result: ");
    while(l.head != NULL){
        if(i % 2 == 0){
            found = true;
            printf("%d ", l.head->data);
        }
        l.head = l.head->link;
        i++;
    }
    if(found == false || temp == NULL)
        printf("No nodes were found.\n");
}

void print_request(List l, int i)
{
    void (*choose[])(List) = {print_odd, print_even, print_node_at_oddPos, print_node_at_evenPos};
    (*choose[i])(l);
}

Node *find_x(List l, int x)
{
    Node *temp = NULL;
    while(l.head != NULL && l.head->data != x){
        l.head = l.head->link;
    }
    temp = l.head;

    if(temp == NULL)
        return NULL;
    return temp;
}

int count_x(List l, int x)
{
    int count = 0;
    while(l.head != NULL){
        if(l.head->data == x)
            count++;
        l.head = l.head->link;
    }
    return count;
}

int find_min(List l)
{
    int min = l.head->data;
    while(l.head != NULL){
        if(l.head->data < min)
            min = l.head->data;
        l.head = l.head->link;
    }
    return min;
}

int find_max(List l)
{
    int max = l.head->data;
    while(l.head != NULL){
        if(l.head->data > max)
            max = l.head->data;
        l.head = l.head->link;
    }
    return max;
}

int find_odd_max(List l)
{
    int max = l.head->data;
    while(l.head != NULL){
        if(l.head->data % 2 != 0 && l.head->data > max)
            max = l.head->data;
        l.head = l.head->link;
    }
    if(max % 2 == 0)
        return NOT_FOUND;
    else
        return max;
}

int find_even_min(List l)
{
    int min = l.head->data;
    while(l.head != NULL){
        if(l.head->data % 2 == 0 && l.head->data < min)
            min = l.head->data;
        l.head = l.head->link;
    }
    if(min % 2 != 0)
        return NOT_FOUND;
    else
        return min;
}

void finding_request(List l, int i, int *found_num, bool *found, bool *list_empty)
{
    if(l.head == NULL)
        return;
    *list_empty = false;
    int (*choose[])(List) = {find_max, find_min, find_odd_max, find_even_min};
    *found_num = (*choose[i])(l);
    if(*found_num != NOT_FOUND)
        *found = true;
    else
        *found = false;
}

void del_selection(List *l, int pos)
{
    if(pos == 1){
        del_beginning(l);
    }
    else if(pos == count_node(*l) - 1)
        del_end(l);
    else
        del_mid(l, pos);
}

void del_max(List *l)
{
    Node *temp = l->head;
    int pos = 0;
    int max = NOT_FOUND;
    max = find_max(*l);
    if(max == NOT_FOUND){
        printf("Have no max value to delete.\n");
        return;
    }
    while(temp != NULL){
        if(temp->data == max)
            del_selection(l, pos + 1);
        temp = temp->link;
        pos++;
    }
}

void del_min(List *l)
{
    Node *temp = l->head;
    int pos = 0;
    int min = NOT_FOUND;
    min = find_min(*l);
    if(min == NOT_FOUND){
        printf("Have no min value to delete.\n");
        return;
    }
    while(temp != NULL){
        if(temp->data == min)
            del_selection(l, pos + 1);
        temp = temp->link;
        pos++;
    }
}

void deleting_request(List *l, int i)
{
    if(l->head == NULL){
        printf("Your list is empty.\n");
        return;
    }
    void (*choose[])(List *) = {del_max, del_min};
    (*choose[i])(l);
}

