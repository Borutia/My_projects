#include <iostream>

using namespace std;

struct DoubleList
{
    int data;
    DoubleList *next;
    DoubleList *prev;
};

DoubleList *head;

void AddList(int value, int position)
{
    DoubleList *node=new DoubleList;
    node->data=value;
    if (head==NULL)
    {
        node->next=node;
        node->prev=node;
        head=node;
    }
    else
    {
        DoubleList *p=head;
        for(int i=position; i>1; i--)
            p=p->next;
        p->prev->next=node;
        node->prev=p->prev;
        node->next=p;
        p->prev=node;
    }
    cout<<"\nЭлемент добавлен...\n\n";
}

int DeleteList(int position)
{
    if (head==NULL)
    {
        cout<<"\nСписок пуст\n\n";
        return 0;
    }
    if (head==head->next)
    {
        delete head;
        head=NULL;
    }
    else
    {
        DoubleList *a=head;
        for (int i=position; i>1; i--)
            a=a->next;
        if (a==head)
            head=a->next;
        a->prev->next=a->next;
        a->next->prev=a->prev;
        delete a;
    }
    cout<<"\nЭлемент удален...\n\n";
}

void PrintList()
{
    if (head==NULL)
        cout<<"\nСписок пуст\n\n";
    else
    {
        DoubleList *a=head;
        cout << "\nЭлементы списка: ";
        do
        {
            cout << a->data << " ";
            a = a->next;
        } while(a!=head);
        cout<<"\n\n";
    }
}

void search_element(int value)
{
    bool check = true;
    if (head==NULL)
        cout<<"\nСписок пуст\n\n";
    else
    {
        DoubleList *a=head;
        do
        {
            if(a->data == value)
            {
                cout << "Элемент в списке присутсвует" << endl;
                check = false;
                break;
            }
            a = a->next;
        } while(a!=head);
    }
    if(check)
        cout << "Элемент в списке отсутствует" << endl;
    cout<<"\n\n";
}

int main()
{
    setlocale(LC_ALL, "Rus");
    int value, position, x;
    do
    {
        cout << "1. Добавить элемент" << endl;
        cout << "2. Удалить элемент" << endl;
        cout << "3. Вывести список" << endl;
        cout << "4. Поиск по значению" << endl;
        cout << "0. Выйти" << endl;
        cout << "\nНомер операции > ";
        cin >> x;
        switch (x)
        {
            case 1:
                cout<<"Значение > "; cin>>value;
                cout<<"Позиция > "; cin>>position;
                AddList(value, position);
                break;
            case 2:
                cout<<"Позиция > "; cin>>position;
                DeleteList(position);
                break;
            case 3:
                PrintList();
                break;
            case 4:
                cout << "Значение > ";
                cin >> value;
                search_element(value);
        }
    } while (x!=0);
    return 0;
}