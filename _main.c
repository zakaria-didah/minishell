#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void	parr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("[%s]\n", arr[i++]);
	}
}

int main(int ac, char **arg){
	int i = 1;
	printf("%d\n", ~i);
	printf("%d\n", i);
}
