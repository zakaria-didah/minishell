/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garb_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:55:54 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/14 10:56:35 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garb.h"

t_list	**parena_head(void)
{
	static t_list	*lst = NULL;
	t_mem			*mem;

	if (!lst)
	{
		mem = malloc(sizeof(t_mem));
		mem->offset = 0;
		mem->size = ARENA_SIZE;
		mem->mempool = malloc(mem->size);
		ft_bzero(mem->mempool, mem->size);
		lst = malloc(sizeof(t_list));
		lst->content = mem;
		lst->next = NULL;
	}
	return (&lst);
}

void	reset_arena(void)
{
	t_list	*alloc;
	t_mem	*mem;
	t_list	*tmp;

	alloc = *arena_head();
	if (alloc)
	{
		mem = alloc->content;
		ft_bzero(mem->mempool, mem->size);
		mem->offset = 0;
	}
	tmp = alloc;
	if (alloc->next)
		clear_arena(alloc->next);
	tmp->next = NULL;
}

int	clear_arena(t_list *alloc)
{
	t_list	*tmp;
	t_mem	*mem;

	tmp = NULL;
	if (!alloc)
		alloc = *arena_head();
	while (alloc)
	{
		mem = alloc->content;
		free(mem->mempool);
		free(mem);
		tmp = alloc;
		alloc = alloc->next;
		free(tmp);
	}
	return (1);
}

t_mem	*realloc_arena(t_list *head)
{
	t_list	*arena;
	t_mem	*new;

	new = malloc(sizeof(t_mem));
	arena = ft_lstlast(head);
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
	alloc = *parena_head();
	while (alloc)
	{
		free(((t_mem *)(alloc->content))->mempool);
		free(alloc->content);
		tmp = alloc;
		alloc = alloc->next;
		free(tmp);
	}
}
