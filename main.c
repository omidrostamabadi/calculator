#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
int main()
{
    char str1[1000];
    char str2[1000];
    char output[1000];
    fgets(str1 , 1000 , stdin);
    str1[strlen(str1)-1]='\0';
    fgets(str2 , 1000 , stdin);
    str2[strlen(str2)-1]='\0';
    //printf("%d\t\t%d" , strlen(str1) , strlen(str2));
    //printf("str1 == %s \n str2 == %s", str1, str2);
    for(int i=0 ; i<strlen(str1) ; i++)
        output[i] = str1[i];
    output[strlen(str1)] = ' ';
    for(int j = strlen(str1)+1,k=0 ; j<=strlen(str1)+strlen(str2);j++,k++)
        output[j] = str2[k];
        output[strlen(str1)+strlen(str2)+1] = '\0';
    printf("%s" , output);
    return 0;
}
