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
    // char *s = ft_calloc(64, C_ARENA);
    // char *d = ft_calloc(64, C_ARENA);
    // char *f = ft_calloc(64, C_ARENA);
    // char *x = ft_calloc(64, C_ARENA);
    // char *z = ft_calloc(64, C_ARENA);
    // char *c = ft_calloc(64, C_ARENA);
    // char *v = ft_calloc(64, C_ARENA);
    // char *h = ft_calloc(64, C_ARENA);

    // pl();
    // reset_arena();
    // printf("\nafter reset\n\n");
    // pl();

    char *s = "hi\"ls     -l\"'hi' hello hi \"hhdhhd\"  ";
    parr(split_(s));
    int i = 55;
    if (i)
        printf("yes\n");


}