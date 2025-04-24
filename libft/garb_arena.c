#include "garb.h"

void	reset_arena(void)
{
	t_list	*alloc;
	t_mem	*mem;

	alloc = *arena_head();
	while (alloc)
	{
		mem = alloc->content;
		ft_bzero(mem->mempool, mem->size);
		mem->offset = 0;
		alloc = alloc->next;
	}
}

int	clear_arena(void)
{
	t_list	*alloc;
	t_list	*tmp;
	t_mem	*mem;

	alloc = *arena_head();
	while (alloc)
	{
		mem = alloc->content;
		if (mem->offset == 0)
		{
			ft_remove(mem->mempool);
			free(mem);
			if (!tmp)
				*arena_head() = alloc->next;
			else
				tmp->next = alloc->next;
			free(alloc);
		}
		tmp = alloc;
		alloc = alloc->next;
	}
	return (1);
}

t_mem	*realloc_arena(void)
{
	t_list	*arena;
	t_mem	*new;

	new = malloc(sizeof(t_mem));
	arena = ft_lstlast(*arena_head());
	new->size = ((t_mem *)arena->content)->size * 2;
	new->mempool = malloc(new->size);
	ft_bzero(new->mempool, new->size);
	new->offset = 0;
	arena->next = malloc(sizeof(t_list));
	arena->next->content = new;
	arena->next->next = NULL;
	return (new);
}

void	dealloc_arena(void)
{
	t_list	*alloc;
	t_list	*tmp;

	alloc = *arena_head();
	while (alloc)
	{
		free(((t_mem *)(alloc->content))->mempool);
		free(alloc->content);
		tmp = alloc;
		alloc = alloc->next;
		free(tmp);
	}
}
