#include <stdio.h>
#include <string.h>

void func(FILE *f1, FILE *f2, int len);
void stars(FILE *f1, FILE *f2, int len);
void deletee(FILE *f1, FILE *f2,  int len);
void quote2(FILE *f1, FILE *f2, int len);
void quote1(FILE *f1, FILE *f2, int len);
int backslash(FILE *f1, int len);

int main()
{
    FILE *project, *f1, *f2;
    project = fopen("project.txt","r");
    char *name_file;
    char str[255];
    while (1) {
        name_file = fgets(str, sizeof(str), project);
        if (name_file == NULL) {
            if (feof(project) != 0) {
                printf("\nЧтение файла закончено\n");
                break;
            } else {
                printf("\nОшибка чтения из файла\n");
                break;
            }
        }
        f1 = fopen(name_file, "r");
        char name[255];
        for(int i=0;i<strlen(name_file);i++)
        {
            if(name_file[i] == '.')
            {
                name[i++] = '.';
                name[i++] = 'w';
                name[i++] = 'c';
                break;
            }
            name[i] = name_file[i];
        }
        //strcat(name, ".wc");
        f2 = fopen(name, "w");
        func(f1, f2, 0);
    }
}


void deletee(FILE *f1, FILE *f2,  int len)
{
    fseek(f1, len, SEEK_SET);
    char c;
    do {
        c = fgetc(f1);
        len++;
        fseek(f1, len, SEEK_SET);
    } while (c != '\n'&& c!=EOF);

    if (c == '\n') {
        if ((backslash(f1, len - 2) == 0 || backslash(f1, len - 2) == 1)) {
            len++;
            fseek(f1, len, SEEK_SET);
            c = fgetc(f1);
            if (c != '\n')
                deletee(f1, f2, len);
            else
                func(f1, f2, len);
        }else
            func(f1, f2, len);
    }
    else
        func(f1, f2, len);
}

void stars(FILE *f1, FILE *f2, int len)
{
    char s1; char s2;
    do{

        fseek(f1, len, SEEK_SET);
        s1 = fgetc(f1);len++;
        if (s1 == '*')
        {

            fseek(f1, len, SEEK_SET);
            s2 = fgetc(f1);
            if (s2 == '/')
            {
                len++;
                func(f1, f2, len);
            }
        }
    } while (s1 != EOF);
    func(f1, f2, len);
}

void quote2(FILE *f1, FILE *f2, int len)
{
    char c;
    fseek(f1, len, SEEK_SET);
    c = fgetc(f1);
    len++;
    while (c != '\n' && c != '\"'&& c!=EOF)
    {
        fputc(c, f2);
        fseek(f1, len, SEEK_SET);
        len++;
        c = fgetc(f1);
    }

    if (c == '\n') {
        if (backslash(f1, len - 2) == 0|| backslash(f1, len - 2) == 2){
            fputc(c, f2);
            len++;
            func(f1, f2, len);
        }
        else {
            fputc(c, f2); len++;
            quote2(f1, f2, len);
        }
    }
    if (c == EOF)
        func(f1, f2, len);
    else {
        if (backslash(f1, len - 2) == 0 || backslash(f1, len - 2) == 2) {//������ �����������
            fputc(c, f2);
            func(f1, f2, len);
        }
        else {
            fputc(c, f2);
            quote2(f1, f2, len);
        }

    }
}

void quote1(FILE *f1, FILE *f2, int len)
{
    char c;
    fseek(f1, len, SEEK_SET);
    c = fgetc(f1);
    len++;
    while (c != '\n' && c != (char)39 && c!=EOF)
    {
        fputc(c, f2);
        fseek(f1, len, SEEK_SET);
        len++;
        c = fgetc(f1);
    }
    if (c == (char)39)
    {
        if (backslash(f1, len - 2) == 0 || backslash(f1, len - 2) == 2) {
            fputc(c, f2);
            func(f1, f2, len);
        }
        else {
            fputc(c, f2);
            quote1(f1, f2, len);
        }

    }
    if (c == EOF)
        func(f1, f2, len);
    else
        func(f1, f2, len);
}

int backslash(FILE *f1, int len)
{
    char c; int k = 0;
    fseek(f1, len, SEEK_SET);
    c = fgetc(f1);
    while (c == '\\') {
        k++;
        len--;
        fseek(f1, len, SEEK_SET);
        c = fgetc(f1);
    } if (k == 0)return(2);
    else if (k % 2 == 0 && k != 0)
        return(0);
    else return(1);
}

void func(FILE *f1, FILE *f2, int len)
{
    char s1 = 0; char s2 = 0;
    fseek(f1, len, SEEK_SET);
    s1 = fgetc(f1);
    if (s1 != EOF)
    {
        len++;
        fseek(f1, len, SEEK_SET);
        s2 = fgetc(f1);
        if ((s1 == '/') && (s2 == '/'))
        {
            deletee(f1, f2, len);
        }

        if ((s1 == '/') && (s2 == '*'))
        {
            len++;
            stars(f1, f2, len);
        }
        if (s1 == '\"')
        {
            fputc(s1, f2);
            quote2(f1, f2, len);
        }
        if (s1 == (char)39)
        {
            fputc(s1, f2);
            quote1(f1, f2, len);
        }
        if (s1 == '\n'&&s2 == '\n') {
            len++;
            fputc(s1, f2);
            func(f1, f2, len);
        }
        else
        {
            fputc(s1, f2);
            func(f1, f2, len);
        }
    }
    fclose(f1);
    fclose(f2);
}