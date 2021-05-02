#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
typedef struct Node Pnode;
struct Node
{
	int item;
	Pnode* next;
};


typedef struct Stack STACK;
struct Stack
{
	Pnode *First;
	int count;
};

void InitStack(STACK*);
void Push(STACK*, int item);
void Pop(STACK*);
void Clear(STACK*);
void Show(STACK);
int Peek(STACK);
void max_element(STACK);
void is_empty(STACK*);
void InputItem(STACK*);
void search_element(STACK);

int menu();

int main(int argc, char *argv[])
{
	STACK stack;
	InitStack(&stack);
	setlocale(LC_ALL, "Russian");
	int n = 0;
	while (n != 6)
	{
		n = menu();

		switch (n)
		{
		case 1:Show(stack); break;
		case 2:InputItem(&stack); break;
		case 3:Pop(&stack); break;
		case 4:Clear(&stack); break;
		case 5:is_empty(&stack); break;
		case 6:search_element(stack); break;
		case 7:max_element(stack); break;
		case 8:break;
		}
		system("pause");
	}

}

void is_empty(STACK* stack)
{
	if (stack->count == 0)
		printf("Список пуст!");
	else
		printf("Список не пуст!");
	printf("\n");
}

void search_element(STACK stack)
{
	int element;
	printf("Введите элемент для поиска: ");
	scanf("%d", &element);
	Pnode *node = stack.First;
	int i;
	bool check = false;
	for (i = 0; i<stack.count; i++)
	{
		if (element == node->item)
		{
			check = true;
			break;
		}
		node = node->next;
	}
	if (check)
		printf("Элемент присутствует.");
	else
		printf("Элемент отсутствует.");
	printf("\n");
}

void InitStack(STACK* stack)
{
	stack->count = 0;
	stack->First = NULL;
}

void Push(STACK* stack, int item)
{
	Pnode *node;
	node = (Pnode*)malloc(sizeof(Pnode));
	node->item = item;
	node->next = stack->First;
	stack->First = node;
	stack->count++;
}


void Pop(STACK* stack)
{
	Pnode *first = stack->First;
	Pnode *next = first->next;
	free(first);
	stack->First = next;
	stack->count--;
}


void Clear(STACK* stack)
{
	int n = stack->count, i;
	for (i = 0; i<n; i++)
		Pop(stack);
}

void Show(STACK stack)
{
	Pnode *node = stack.First;
	printf("Стек: ");
	int i;
	for (i = 0; i<stack.count; i++)
	{
		printf("%d\t", node->item);
		node = node->next;
	}
	printf("\n");
}

void max_element(STACK stack)
{
	Pnode *node = stack.First;
	int max_elem = node->item;
	for (int i = 0; i<stack.count; i++)
	{
		if (max_elem < node->item)
			max_elem = node->item;
		node = node->next;
	}
	printf("Максимальный элемент: %d\n", max_elem);
}




int menu()
{
	int n = 0;
	while ((n <= 0) || (n > 8))
	{
		system("cls");
		printf("Стек.\n");
		printf("1) Показать стек;\n");
		printf("2) Добавить в начало;\n");
		printf("3) Удалить в начале;\n");
		printf("5) Проверка на пустоту\n");
		printf("6) Поиск элемента\n");
		printf("7) Максимальный элемент;\n");
		printf("8) Выход;\n");
		printf("Введите номер команды: ");
		if (scanf("%d", &n) != 1) scanf("%*s");
	}
	return n;
}

void InputItem(STACK *stack)
{
	int item = 0, k = 0;

	while (k != 1)
	{
		printf("Введите элемент: ");
		k = scanf("%d", &item);
		if (k != 1) scanf("%*s");
	}
	Push(stack, item);
}


