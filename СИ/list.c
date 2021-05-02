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


typedef struct List LIST;
struct List
{
	Pnode *First, *Last;
	int count;
};

void InitList(LIST*);
void AddFirst(LIST*, int item);
void AddLast(LIST*, int item);
void AddAfter(LIST*, int new_item, int item);
void AddBefore(LIST*, int new_item, int item);
void DeleteFirst(LIST*);
void DeleteLast(LIST*);
void DeleteItem(LIST*, int item);
void Clear(LIST* list);
void Show(LIST);
void Add_new_element(LIST *list);
int InputItem();
int menu();
void MenuInput(LIST*);
void MenuDelete(LIST*);
void is_empty(LIST*);
void search_element(LIST);

int main(int argc, char *argv[])
{
	LIST list;
	InitList(&list);
	setlocale(LC_ALL, "Russian");
	int n = 0;
	while (n != 8)
	{
		n = menu();

		switch (n)
		{
		case 1:Show(list); break;
		case 2:MenuInput(&list); break;
		case 3:MenuDelete(&list); break;
		case 4:Clear(&list); break;
		case 5:is_empty(&list); break;
		case 6:search_element(list); break;
		case 7:Add_new_element(&list); break;
		case 8:break;
		}
		system("pause");
	}

}

void InitList(LIST* list)
{
	list->count = 0;
	list->First = NULL;
	list->Last = NULL;
}

void is_empty(LIST* list)
{
	if (list->count == 0)
		printf("Список пуст!");
	else
		printf("Список не пуст!");
	printf("\n");
}

void search_element(LIST list)
{
	int element;
	printf("Введите элемент для поиска: ");
	scanf("%d", &element);
	Pnode *node = list.First;
	int i;
	bool check = false;
	for (i = 0; i<list.count; i++)
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

void AddFirst(LIST* list, int item)
{
	Pnode *node;
	node = (Pnode*)malloc(sizeof(Pnode));
	node->item = item;
	node->next = NULL;
	if (list->count>0)
	{
		node->next = list->First;
		list->First = node;
	}
	else
	{
		list->First = node;
		list->Last = list->First;
	}
	list->count++;
}


void AddLast(LIST* list, int item)
{
	Pnode *node;
	node = (Pnode*)malloc(sizeof(Pnode));
	node->item = item;
	node->next = NULL;
	if (list->count>0)
	{
		list->Last->next = node;
		list->Last = node;
	}
	else
	{
		list->First = node;
		list->Last = list->First;
	}
	list->count++;
}

void AddAfter(LIST* list, int new_item, int item)
{
	Pnode *node, *node_list = list->First;
	node = (Pnode*)malloc(sizeof(Pnode));
	node->item = new_item;
	while (node_list)
	{
		if (node_list->item == item)
		{
			list->count++;
			Pnode *next = node_list->next;
			node->next = next;
			node_list->next = node;
			break;
		}
		node_list = node_list->next;
	}
}

void AddBefore(LIST* list, int new_item, int item)
{
	Pnode *node, *node_list = list->First;
	node = (Pnode*)malloc(sizeof(Pnode));
	node->item = new_item;
	Pnode *prev = NULL;
	while (node_list)
	{
		if (node_list->item == item)
		{
			list->count++;
			if (prev) prev->next = node;
			node->next = node_list;
			break;
		}
		prev = node_list;
		node_list = node_list->next;
	}
}

void DeleteFirst(LIST* list)
{
	Pnode *first = list->First;
	if (list->count>1)
	{
		Pnode *next = first->next;
		free(first);
		list->First = next;
		list->count--;
	}
	else
		if (list->count == 1)
		{
			free(first);
			list->First = NULL;
			list->Last = NULL;
			list->count--;
		}
}
void DeleteLast(LIST* list)
{
	Pnode *last = list->Last;
	if (list->count>1)
	{
		int i = 0; Pnode *prev = list->First;
		for (i = 0; i<list->count - 1; i++)
		{
			prev = prev->next;
		}
		free(last);
		last = prev;
		last->next = NULL;
		list->count--;
	}
	else
		if (list->count == 1)
		{
			free(last);
			list->First = NULL;
			list->Last = NULL;
			list->count--;
		}
}

void DeleteItem(LIST* list, int item)
{
	Pnode *node = list->First, *prev = NULL;
	int i = 0;
	for (i = 0; i<list->count; i++)
	{
		if (node->item == item)
		{
			if (prev) prev->next = node->next;
			free(node);
			list->count--;
			break;
		}
		prev = node;
		node = node->next;
	}
}

void Clear(LIST* list)
{
	Pnode *node = list->First, *prev = NULL;
	int i = 0;
	for (i = 0; i<list->count; i++)
	{
		Pnode *next = node->next;
		free(node);
		node = next;
	}
	list->count = 0;
}

void Show(LIST list)
{
	Pnode *node = list.First;
	printf("Список: ");
	int i;
	for (i = 0; i<list.count; i++)
	{
		printf("%d\t", node->item);
		node = node->next;
	}
	printf("\n");
}

void Add_new_element(LIST *list)
{
	int L;
	printf("Введите L: ");
	scanf("%d", &L);

	int E;
	printf("Введите E: ");
	scanf("%d", &E);

	int k = 0;
	Pnode *curr = list->First;
	Pnode *elem;
	while (curr)
	{
		if (curr->item == E)
		{
			elem = new Pnode();
			elem->item = L;
			elem->next = curr->next;
			curr->next = elem;
			k++;
		}
		curr = curr->next;
	}
	list->count = list->count + k;
	if (k==0)
		printf("Такого числа нет\n");
}



int menu()
{
	int n = 0;
	while ((n <= 0) || (n > 8))
	{
		system("cls");
		printf("Линейный список.\n");
		printf("1) Показать список;\n");
		printf("2) Добавить элемент;\n");
		printf("3) Удалить элемент;\n");
		printf("4) Очистить спискок;\n");
		printf("5) Проверка на пустоту\n");
		printf("6) Поиск элемента\n");
		printf("7) Добавить новый элемент за каждым вхождением;\n");
		printf("8) Выход;\n");
		printf("Введите номер команды: ");
		if (scanf("%d", &n) != 1) scanf("%*s");
	}
	return n;
}

int InputItem()
{
	int n = 0, k = 0;

	while (k != 1)
	{
		printf("Введите элемент: ");
		k = scanf("%d", &n);
		if (k != 1) scanf("%*s");
	}
	return n;
}

void MenuInput(LIST *list)
{
	int k = InputItem();
	int n = 0;
	while ((n <= 0) || (n>5))
	{
		system("cls");
		printf("Добавть элемент\n");
		printf("1) Добавить в начало;\n");
		printf("2) Добавить в конец;\n");
		printf("3) Добавить до определённого элемента;\n");
		printf("4) Добавить после определённого элемента;\n");
		printf("5) Выход;\n");
		printf("Введите номер команды: ");
		if (scanf("%d", &n) != 1) scanf("%*s");
	}
	int p;
	switch (n)
	{
	case 1:AddFirst(list, k); break;
	case 2:AddLast(list, k); break;
	case 3:p = InputItem(); AddBefore(list, k, p); break;
	case 4:p = InputItem(); AddAfter(list, k, p); break;
	case 5:break;
	}

}

void MenuDelete(LIST* list)
{
	int n = 0;
	while ((n <= 0) || (n>4))
	{
		system("cls");
		printf("Удалить элемент\n");
		printf("1) Из начала;\n");
		printf("2) В конце;\n");
		printf("3) Удалить определённый элемент;\n");
		printf("4) Выход;\n");
		printf("Введите номер команды: ");
		if (scanf("%d", &n) != 1) scanf("%*s");
	}
	int k;
	switch (n)
	{
	case 1:DeleteFirst(list); break;
	case 2:DeleteLast(list); break;
	case 3:k = InputItem(); DeleteItem(list, k); break;
	case 4:break;
	}
}


