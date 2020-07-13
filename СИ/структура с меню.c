#include <stdio.h>
#include <stdlib.h>

struct machines{
    char name_machine[20];
    char number[20];
    char name_department[20];
    int year;
    int time;
};

int add_machine(struct machines *machine, int size)
{
    printf("\n");
    printf("Название станка: ");
    scanf("%s",&machine[size].name_machine);
    printf("Инвентарный номер: ");
    scanf("%s",&machine[size].number);
    printf("Название цеха: ");
    scanf("%s",&machine[size].name_department);
    printf("Год ввода в эксплуатацию: ");
    scanf("%d",&machine[size].year);
    printf("Время эксплуатации: ");
    scanf("%d",&machine[size].time);
    size++;
    return size;
}

int save_in_file(struct machines *machine, int size)
{
    FILE * output = fopen("output.txt","w");
    for(int i=0;i<size;i++)
    {
        fprintf(output,"%s\n",machine[i].name_machine);
        fprintf(output,"%s\n",machine[i].number);
        fprintf(output,"%s\n",machine[i].name_department);
        fprintf(output,"%d\n",machine[i].year);
        fprintf(output,"%d\n",machine[i].time);
    }
    printf("Данные сохранены!\n\n");
    fclose(output);
    size = 0;
    return size;
}

int download(struct machines *machine)
{
    int size = 0;
    FILE *input = fopen("output.txt","r");
    while(!feof(input))
    {
        fscanf(input,"%s",&machine[size].name_machine);
        fscanf(input,"%s",&machine[size].number);
        fscanf(input,"%s",&machine[size].name_department);
        fscanf(input,"%d",&machine[size].year);
        fscanf(input,"%d",&machine[size].time);
        size++;
    }
    fclose(input);
    size--;
    return size;
}

void print_information(struct machines *machine, int size)
{
    printf(" № |\tНазвание\t|\tИнвентарный\t|\t Название\t|\tГод ввода в \t|\t\tВремя\t\t|\n");
    printf("   |\tстанка\t\t|\t\tномер \t|\t\tцеха\t|\tэксплуатацию \t|\tэксплуатации\t|\n");
    for(int i=0;i<size;i++)
    {
        printf(" %d |\t %s\t\t|\t\t%s\t|\t\t%s\t|\t\t%d\t\t|\t\t%d\t\t|\n",i+1,
                machine[i].name_machine, machine[i].number,
                machine[i].name_department,
                machine[i].year, machine[i].time);

    }
}

int add_machine_in_number(struct machines *machine, int size)
{
    int number;
    printf("На какое место добавить: ");
    scanf("%d",&number);
    number-=1;
    struct machines t;

    printf("Название станка: ");
    scanf("%s",&t.name_machine);
    printf("Инвентарный номер: ");
    scanf("%s",&t.number);
    printf("Название цеха: ");
    scanf("%s",&t.name_department);
    printf("Год ввода в эксплуатацию: ");
    scanf("%d",&t.year);
    printf("Время эксплуатации: ");
    scanf("%d",&t.time);
    size++;

    for(int i=size;i>number;i--)
    {
       machine[i] = machine[i-1];
    }
    machine[number] = t;
    return size;
}

int delete_one_machine(struct machines *machine, int size)
{
    int number;
    printf("Под каким номером удалить: ");
    scanf("%d",&number);
    number-=1;
    size--;
    for(int i=number;i<size;i++) {
        machine[i] = machine[i + 1];
    }
    return size;
}

void my_func_about_machine(struct machines *machine, int size)
{
    int temp_time;
    printf("Введите время эксплуатации: ");
    scanf("%d",&temp_time);
    printf(" № |\tНазвание\t|\tИнвентарный\t|\t Название\t|\tГод ввода в \t|\t\tВремя\t\t|\n");
    printf("   |\tстанка\t\t|\t\tномер \t|\t\tцеха\t|\tэксплуатацию \t|\tэксплуатации\t|\n");
    for(int i=0;i<size;i++)
    {
        if(machine[i].time > temp_time) {
            printf(" %d |\t %s\t\t|\t\t%s\t|\t\t%s \t|\t\t%d\t\t|\t\t%d\t\t|\n", i + 1,
                   machine[i].name_machine, machine[i].number,
                   machine[i].name_department,
                   machine[i].year, machine[i].time);
        }

    }
}


void menu(struct machines *machine)
{
    int select_number;
    int size = 0;
    for(;;)
    {
        printf("1)Добавить станок\n");
        printf("2)Сохранить в файл\n");
        printf("3)Загрузить из файла\n");
        printf("4)Вывод на монитор\n");
        printf("5)Добавь на определенное место\n");
        printf("6)Удалить по указанному номеру\n");
        printf("7)Вывести информацию о станках, время эксплуатации которых больше заданного\n");
        printf("8)Выход\n");
        printf("Выберите цифру:");
        scanf("%d",&select_number);
        switch(select_number)
        {
            case 1:{
                size = add_machine(machine,size);
                break;
            }
            case 2:{
                size = save_in_file(machine,size);
                break;
            }
            case 3:{
                size = download(machine);
                break;
            }
            case 4:{
                print_information(machine,size);
                break;
            }
            case 5:{
                size = add_machine_in_number(machine,size);
                break;
            }
            case 6:{
                size = delete_one_machine(machine,size);
                break;
            }
            case 7:{
                my_func_about_machine(machine,size);
                break;
            }
            case 8:{
                exit(0);
            }
            default:{
                break;
            }

        }
    }
}

int main()
{
    struct machines machine[100];
    menu(machine);

    return 0;
}