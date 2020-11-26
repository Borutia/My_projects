#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int N;
    scanf("%d",&N);
    fflush(stdin);
    char result_output[255];
    for(int i=0;i<N;i++) {
        char text[255];
        char str1[255];
        char str2[255];
        gets(text);
        char *pch = strtok(text, " ");
        strcpy(str1, pch);
        pch = strtok(NULL, " ");
        strcpy(str2, pch);

        char *it1 = str1;
        char *it11, *it2;
        while (it1[0]) {
            it11 = it1;
            it2 = str2;
            while (*it11 == *it2 && *it2) {
                it2++;
                it11++;
            }
            if (*it11 == 0) {
                int len = it11 - str1;
                len += it2 - str2;
                char *result = (char*)malloc(len);
                strcpy(result, str1);
                strcat(result, it2);
                strcat(result, "\n");
                strcat(result_output,result);
                break;
            }
            it1++;
        }
    }
    printf("%s", result_output);
    return 0;
}