#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char words_for_check[3][100];
//функция для нахождения самого длинного слова
char* max_word(char *str, char *delim){

    char* copy = (char*)malloc(strlen(str + 1));
    char* token;
    char* max_word = (char*)malloc(strlen(str + 1));

    strcpy(copy, str);

    for(token = strtok(copy, delim);token != 0;token = strtok(0, delim)){
        if(strlen(token) >= strlen(max_word))//если нужно первое самое длинное то > если последнее самое длинное, то >=
            strcpy(max_word, token);
    }
    return max_word;
}

//функция удаления самого длинного слова в строке
char* delete_word(char* str, char* word, char *delim){
    char* copy = (char*)malloc(strlen(str + 1));
    char* token;
    char* new_str = (char*)malloc(strlen(str + 1));

    strcpy(copy, str);

    for(token = strtok(copy, delim);token != 0;token = strtok(0, delim)){
        if(strcmp(token, word) == 0) continue;

        strcat(new_str, token);

        token = strtok(0, delim);
        if(!token)
            break;
        else{
            strcat(new_str, " ");

            if(strcmp(token, word) == 0) continue;

            strcat(new_str, token);
            strcat(new_str, " ");
        }
    }
    return new_str;
}
//функция для проверки трех слов в строке
int check_str(char *str, char *delim)
{
    char* copy = (char*)malloc(strlen(str + 1));
    char* token;

    strcpy(copy, str);
    int check;
    check = 0;
    for(token = strtok(copy, delim);token != 0;token = strtok(0, delim))
    {
        for(int i=0;i<3;i++)
        {
            if(strcmp(token, words_for_check[i]) == 0)
            {
                check++;
            }
        }
    }
    if(check >= 3)
        return 0;
    return 1;
}
//функция для проверки одного слова в строке
int check_str_for_delete(char *str, char *delim)
{
    char* copy = (char*)malloc(strlen(str + 1));
    char* token;

    strcpy(copy, str);
    int check;
    check = 0;
    for(token = strtok(copy, delim);token != 0;token = strtok(0, delim))
    {
        for(int i=0;i<3;i++)
        {
            if(strcmp(token, words_for_check[i]) == 0)
            {
                check++;
            }
        }
    }
    if(check >= 1)
        return 1;
    return 0;
}

//главная функция
int main() {

    printf("Input words\n");
    for(int i=0;i<3;i++)
    {
        printf("Input %d word: ",i+1);
        gets(words_for_check[i]);
    }
    printf("Input delim: ");
    char *delim = (char*)malloc(10);
    gets(delim);

    char str[100][100];
    char *temp_str[100];
    int i = 0;
    printf("Input strings:\n");
    do
    {
        printf("Input %d string: ",i+1);
        gets(temp_str);
        strcpy(str[i],temp_str);
        i++;
    }while(check_str(temp_str,delim));
    int size = i;
    printf("\n");
    for(int i=0;i<size;i++)
    {
        if(check_str_for_delete(str[i],delim))
        {
            printf("String: %s\n",str[i]);
            printf("Max word: %s\n",max_word(str[i],delim));
            printf("edit string: %s\n",delete_word(str[i],max_word(str[i],delim),delim));
            printf("\n");
            continue;
        }
        printf("String: %s\n",str[i]);
        printf("\n");
    }
    return 0;
}
