#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    int p = fork();
    if (p == 0)
    {
        while (1)
        {
            /* code */
        }
        
        /* code */
    }
    else
    {
        int stat = 0;
        waitpid(p,&stat,0);
        printf("%d\n",stat & 255);
        printf("%d\n",stat << 8);
    }
}