#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"


/*⇓⇓⇓⇓ print_array ⇓⇓⇓⇓*/
void	parr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (void)printf("[null]\n");
	printf("{");
	while (arr[i])
	{
		printf("[%s]", arr[i++]);
		if (arr[i])
			printf(", ");
		else
			printf("}\n");
	}
}

int main(int ac, char **av, char **env)
{
    exit(-51);

    
}