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


typedef struct Queue QUEUE;

struct Queue
{
	Pnode *First, *Last;
	int count;
};

void InitQueue(QUEUE*);
void Enqueue(QUEUE*, int item);
void Dequeue(QUEUE*);
void Clear(QUEUE*);
void Show(QUEUE);
void task_queue(QUEUE);
void is_empty(QUEUE*);
void search_element(QUEUE);

void InputItem(QUEUE*);

int menu();

int main(int argc, char *argv[])
{
	QUEUE queue;
	InitQueue(&queue);
	setlocale(LC_ALL, "Russian");
	int n = 0;
	while (n != 8)
	{
		n = menu();

		switch (n)
		{
		case 1:Show(queue); break;
		case 2:InputItem(&queue); break;
		case 3:Dequeue(&queue); break;
		case 4:Clear(&queue); break;
		case 5:is_empty(&queue); break;
		case 6:search_element(queue); break;
		case 7:task_queue(queue); break;
		case 8:break;
		}
		system("pause");
	}

}

void InitQueue(QUEUE* queue)
{
	queue->count = 0;
	queue->First = NULL; queue->Last = NULL;
}

void Enqueue(QUEUE* queue, int item)
{
	Pnode *node;
	node = (Pnode*)malloc(sizeof(Pnode));
	node->item = item;
	node->next = queue->Last;
	queue->Last = node;
	if (queue->count == 0) queue->First = node;
	queue->count++;
}


void Dequeue(QUEUE* queue)
{
	Pnode *first = queue->First;
	Pnode *node = queue->Last;
	free(first); int i;
	for (i = 0; i<queue->count - 1; i++)
	{
		node = node->next;
	}
	queue->First = node;
	queue->count--;
}


void Clear(QUEUE* queue)
{
	int n = queue->count, i;
	Pnode *node = queue->Last;
	for (i = 0; i<n; i++)
	{
		Pnode *next = node->next;
		free(node);
		node = next;
	}
	queue->count = 0;
	queue->First = NULL; queue->Last = NULL;
}

void search_element(QUEUE queue)
{
	int element;
	printf("Введите элемент для поиска: ");
	scanf("%d", &element);
	bool check = false;
	Pnode *node = queue.Last;
	printf("Очередь: ");
	int i;
	for (i = 0; i<queue.count; i++)
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

void Show(QUEUE queue)
{
	Pnode *node = queue.Last;
	printf("Очередь: ");
	int i;
	for (i = 0; i<queue.count; i++)
	{
		printf("%d\t", node->item);
		node = node->next;
	}
	printf("\n");
}

void is_empty(QUEUE* queue)
{
	if (queue->count == 0)
		printf("Очередь пустая!");
	else
		printf("Очередь не пустая!");
	printf("\n");
}



int menu()
{
	int n = 0;
	while ((n <= 0) || (n > 8))
	{
		system("cls");
		printf("Очередь.\n");
		printf("1) Показать очередь;\n");
		printf("2) Добавить в очередь;\n");
		printf("3) Удалить из очереди;\n");
		printf("4) Очистить очередь;\n");
		printf("5) Проверка на пустоту;\n");
		printf("6) Поиск элемента;\n");
		printf("7) Сформировать очередь из двух по одному элементу ;\n");
		printf("8) Выход;\n");
		printf("Введите номер команды: ");
		if (scanf("%d", &n) != 1) scanf("%*s");
	}
	return n;
}

void task_queue(QUEUE queue)
{
	QUEUE queue2;
	InitQueue(&queue2);
	printf("Создаем вторую очередь: \n");
	for (int i = 0; i < queue.count; i++)
		InputItem(&queue2);

	Pnode *node2 = queue2.Last;

	Pnode *node = queue.Last; 

	int arr[1000];
	int counter = 0;
	for (int i = 0; i < queue.count; i++)
	{
		arr[counter++] = node->item;
		node = node->next;
		arr[counter++] = node2->item;
		node2 = node2->next;
	}
	for (int i = 0; i < counter; i++)
	{
		bool t = true;
		for (int j = i + 1; j < counter; j++)
		{
			if (arr[i] == arr[j])
				t = false;
		}
		if (t)
		{
			printf("%d ", arr[i]);
		}
	}
	printf("\n");
}



void InputItem(QUEUE *queue)
{
	int item = 0, k = 0;
	while (k != 1)
	{
		printf("Введите элемент: ");
		k = scanf("%d", &item);
		if (k != 1) scanf("%*s");
	}
	Enqueue(queue, item);
}


