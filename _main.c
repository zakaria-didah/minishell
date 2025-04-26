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

int main(){
    char *s = ft_calloc(64, C_ARENA);
    char *d = ft_calloc(64, C_ARENA);
    char *f = ft_calloc(64, C_ARENA);
    char *x = ft_calloc(64, C_ARENA);
    char *z = ft_calloc(64, C_ARENA);
    char *c = ft_calloc(64, C_ARENA);
    char *v = ft_calloc(64, C_ARENA);
    char *h = ft_calloc(64, C_ARENA);

    pl();
    reset_arena();
    printf("\nafter reset\n\n");
    pl();



}