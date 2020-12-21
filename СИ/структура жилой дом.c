#include <stdio.h>
#include <stdlib.h>

struct Apartments{
    char address[50];
    int count_of_apartments;
    int all_square;
    char name_organization[50];
};

int save_in_file(struct Apartments *apart, int size)
{
    FILE * output = fopen("output.txt","w");
    for(int i=0;i<size;i++)
    {
        fprintf(output,"%s\n",apart[i].address);
        fprintf(output,"%d\n",apart[i].count_of_apartments);
        fprintf(output,"%d\n",apart[i].all_square);
        fprintf(output,"%s\n",apart[i].name_organization);
    }
    printf("Данные сохранены!\n\n");
    fclose(output);
    size = 0;
    return size;
}

int download(struct Apartments *apart)
{
    int size = 0;
    FILE *input = fopen("output.txt","r");
    while(!feof(input))
    {
        fscanf(input,"%s",&apart[size].address);
        fscanf(input,"%d",&apart[size].count_of_apartments);
        fscanf(input,"%d",&apart[size].all_square);
        fscanf(input,"%s",&apart[size].name_organization);
        size++;
    }
    printf("Данные загружены!\n\n");
    fclose(input);
    size--;
    return size;
}

void print_information(struct Apartments *apart, int size)
{
    for(int i=0;i<size;i++)
    {
        printf("%d: %s %d %d %s\n", i+1, apart[i].address,
               apart[i].count_of_apartments,
               apart[i].all_square,
               apart[i].name_organization);
    }
}

int add_apart_in_number(struct Apartments *apart, int size)
{
    int number;
    printf("На какое место добавить: ");
    scanf("%d",&number);
    number-=1;
    if(number > size)
        number = size;
    struct Apartments t;
    printf("Адрес: ");
    scanf("%s",&t.address);
    printf("Число квартир: ");
    scanf("%d",&t.count_of_apartments);
    printf("Общая площадь квартир: ");
    scanf("%d",&t.all_square);
    printf("Наименование обслуживающей организации: ");
    scanf("%s",&t.name_organization);
    size++;

    for(int i=size;i>number;i--)
    {
        apart[i] = apart[i-1];
    }
    apart[number] = t;
    return size;
}

int delete_one_apart(struct Apartments *apart, int size)
{
    int number;
    printf("Под каким номером удалить: ");
    scanf("%d",&number);
    number-=1;
    size--;
    for(int i=number;i<size;i++) {
        apart[i] = apart[i + 1];
    }
    return size;
}

void edit_node(struct Apartments *apart)
{
    int number;
    printf("Под каким номером удалить: ");
    scanf("%d",&number);
    number-=1;
    int select_number;
    int check_return = 0;
    for(;;)
    {
        if(check_return == 1)
        {
            break;
        }
        printf("\n");
        printf("Что хотите изменить?\n");
        printf("1)Адрес\n");
        printf("2)Число квартир\n");
        printf("3)Общая площадь квартир\n");
        printf("4)Наименование обслуживающей организации\n");
        printf("5)Назад\n");
        printf("Выберите цифру:");
        scanf("%d",&select_number);
        switch (select_number) {
            case 1:{
                printf("Новый адрес: ");
                scanf("%s",&apart[number].address);
                break;
            }
            case 2:{
                printf("Новое число квартир: ");
                scanf("%s",&apart[number].count_of_apartments);
                break;
            }
            case 3:{
                printf("Новая общая площадь квартир: ");
                scanf("%s",&apart[number].all_square);
                break;
            }
            case 4:{
                printf("Новое наименование обслуживающей организации: ");
                scanf("%d",&apart[number].name_organization);
                break;
            }
            case 5:{
                check_return = 1;
                break;
            }
            default:{
                break;
            }
        }
    }

}

void task_about_apart(struct Apartments *apart, int size)
{
    struct Apartments goods[100];
    int goods_count = 0;
    int count_apart;
    printf("Введите число квартир для сравнения\n");
    scanf("%d", &count_apart);
    for(int i=0;i<size;i++)
    {
        if(count_apart < apart[i].count_of_apartments)
        {
            goods[goods_count++] = apart[i];
            printf("%d: %s %d %d %s\n", i+1, apart[i].address,
                   apart[i].count_of_apartments,
                   apart[i].all_square,
                   apart[i].name_organization);
        }
    }
    for (int i = 0; i < goods_count - 1; i++) {
        for (int j = 0; j < goods_count - i - 1; j++) {
            if (goods[j].name_organization > goods[j + 1].name_organization) {
                struct Apartments temp = goods[j];
                goods[j] = goods[j + 1];
                goods[j + 1] = temp;
            }
            else if(goods[j].name_organization == goods[j + 1].name_organization)
            {
                if (goods[j].all_square > goods[j + 1].all_square) {
                    struct Apartments temp = goods[j];
                    goods[j] = goods[j + 1];
                    goods[j + 1] = temp;
                }
            }
        }
    }
}


void menu(struct Apartments *apart)
{
    int size = 0;
    for(;;)
    {
        int select_number;
        printf("\n");
        printf("1)Загрузить из файла\n");
        printf("2)Работа с данными\n");
        printf("3)Сохранить в файл\n");
        printf("4)Выход\n");
        printf("Выберите цифру:");
        scanf("%d",&select_number);
        switch(select_number)
        {
            case 1:{
                size = download(apart);
                break;
            }
            case 2:{
                int check_return = 0;
                for(;;)
                {
                    if(check_return == 1)
                    {
                        break;
                    }
                    int select;
                    printf("\n");
                    printf("1)Вывод всех записей\n");
                    printf("2)Добавить запись по номеру\n");
                    printf("3)Удалить запись по номеру\n");
                    printf("4)Изменить запись по номеру\n");
                    printf("5)Вывести число квартир в которых больше указанного значения\n");
                    printf("6)Назад\n");
                    printf("Выберите цифру:");
                    scanf("%d", &select);
                    switch(select)
                    {
                        case 1:{
                            print_information(apart, size);
                            break;
                        }
                        case 2:{
                            size = add_apart_in_number(apart,size);
                            while(getchar() != '\n'){
                                continue;
                            }
                            break;
                        }
                        case 3:{
                            size = delete_one_apart(apart,size);
                            break;
                        }
                        case 4:{
                            edit_node(apart);
                            while(getchar() != '\n'){
                                continue;
                            }
                            break;
                        }
                        case 5:{
                            task_about_apart(apart, size);
                            break;
                        }
                        case 6:{
                            check_return = 1;
                            break;
                        }
                        default:{
                            break;
                        }
                    }
                }
                break;
            }
            case 3:{
                size = save_in_file(apart,size);
                break;
            }
            case 4:{
                exit(0);
                break;
            }
            default:{
                break;
            }
        }
    }
}

int main()
{
    struct Apartments apart[100];
    menu(apart);

    return 0;
}