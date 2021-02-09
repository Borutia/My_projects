#include <stdio.h>
#include <string.h>

int main(int argc, char * argv[]) {
    if(argc == 1) {
        printf("Command line has no arguments\n");
        return 0;
    }
    if(argc == 3)
    {
        if(strcmp(argv[1], "-x") == 0)
        {
            char str[1024][1024];
            int size;
            printf("Input amount str: ");
            scanf("%d",&size);
            char new_line;
            scanf("%c", &new_line);
            for(int i = 0;i<size;i++)
            {
                printf("input str %d: ", i);
                gets(str[i]);
            }
            for(int i = 0;i<size;i++)
            {
                if(strstr (str[i], argv[2]))
                    printf("str: %s\n", str[i]);
            }
        }
    }
    else if(argc == 4)
    {
        if((strcmp(argv[1], "-x") == 0) && strcmp(argv[2], "-n") == 0)
        {
            char str[1024][1024];
            int size;
            printf("Input amount str: ");
            scanf("%d",&size);
            char new_line;
            scanf("%c", &new_line);
            for(int i = 0;i<size;i++)
            {
                printf("input str %d: ", i);
                gets(str[i]);
            }
            for(int i = 0;i<size;i++)
            {
                if(strstr (str[i], argv[3]))
                    printf("str %d: %s\n", i, str[i]);
            }
        }
    }
    else
    {
        printf("Bad arguments\n");
    }

    return 0;
}