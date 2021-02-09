#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char * argv[]) {
    if(argc == 1) {
        printf("Command line has no arguments\n");
        return 0;
    }
    if(argc == 2)
    {
        printf("Text: ");
        puts(argv[1]);
    }
    else if(argc == 3)
    {
        if(strcmp(argv[2], "-d") == 0)
        {
            for(int i=0;i<strlen(argv[1]);i++)
            {
                if(!isdigit(argv[1][i]))
                    printf("%c",argv[1][i]);
            }
            printf("\n");
        }
        else if(strcmp(argv[2], "-r") == 0)
        {
            char numbers[1024];
            int counter_numbers = 0;
            for(int i=0;i<strlen(argv[1]);i++)
            {
                if(isdigit(argv[1][i]))
                {
                    numbers[counter_numbers++] = argv[1][i];
                }
            }
            for(int i=0;i<strlen(argv[1]);i++){
                if(isdigit(argv[1][i]))
                {
                    argv[1][i] = numbers[--counter_numbers];
                }
            }
            puts(argv[1]);
            printf("\n");
        }
        else
        {
            printf("Bad arguments\n");
        }
    }
    else
    {
        printf("Bad arguments\n");
    }

    return 0;
}