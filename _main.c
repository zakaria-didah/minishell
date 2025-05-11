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


int is_directory(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}

int is_executable(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return (statbuf.st_mode & S_IXUSR) || 
           (statbuf.st_mode & S_IXGRP) || 
           (statbuf.st_mode & S_IXOTH);
}


int main(){
 if (access(NULL, X_OK) == 0)
 {
    printf("test is executable\n");
 }
 else
 {
    printf("test is not executable\n");
 }
 if (is_directory(NULL))
 {
    printf("test is directory\n");
 }
 else
 {
    printf("test is not directory\n");
 }
    
}