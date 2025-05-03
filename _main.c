#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"


char *foo(char *str)
{
    char *new_str;
    int i = 0;
    int j = 0;
    char c = 128;



    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '"')
            str[i] = c;
        i++;
    }
    return (str);
}

int main(){
    char *str = strdup("'hello' \"world\"");
    char *new_str = foo(str);
    printf("%s\n", new_str);
    return 0;
    
}