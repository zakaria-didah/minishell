#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int pl(){
    t_list *alloc = *arena_head();
    while(alloc){
    t_mem *mem = alloc->content;
    printf("offset: %zu\n", mem->offset);
    printf("size: %zu\n", mem->size);
    printf("mempool: %s\n", mem->mempool);
    printf("\n");
    alloc = alloc->next;

}
return 0;
}

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

int main(){
    char **tmp = NULL;
    if (!tmp[1])
        printf("null\n");
    else
        printf("not null\n");


}