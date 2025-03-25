/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:41:16 by zdidah            #+#    #+#             */
/*   Updated: 2025/02/02 10:39:14 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garb.h"

t_garb	**_get_head(void)
{
	static t_garb	*head = NULL;

	return (&head);
}

void	_link_list(t_garb *node)
{
	t_garb	**head;

	head = _get_head();
	if (!*head)
	{
		(*head) = node;
	}
	else
	{
		node->prev = NULL;
		node->next = *head;
		(*head)->prev = node;
		*head = node;
	}
}

void	ft_free(void)
{
	t_garb	*tmp;
	t_garb	*head;

	head = *_get_head();
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->ptr);
	}
	dealloc_arena();
}

void	*add_garb(void *ptr)
{
	t_garb	*node;

	node = ft_calloc(sizeof(t_garb));
	if (!node)
		return (NULL);
	node->ptr = ptr;
	node->prev = NULL;
	node->next = NULL;
	_link_list(node);
	return (ptr);
}

t_list	**arena_head(void)
{
	static t_list	*lst = NULL;
	t_mem			*mem ;

	if (!lst)
	{
		mem = malloc(sizeof(t_mem));
		mem->offset = 0;
		mem->size = 1024;
		mem->mempool = malloc(mem->size);
		ft_bzero(mem->mempool, mem->size);
		lst = malloc(sizeof(t_list));
		lst->content = mem;
		lst->next = NULL;
	}
	return (&lst);
}

t_mem	*realloc_arena(void)
{
	t_list	*arena;
	t_mem	*new;

	new = malloc(sizeof(t_mem));
	arena = ft_lstlast(*arena_head());
	new->size = ((t_mem *)arena->content)->size *2;
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

void reset_arena(void)
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

int clear_arena(void)
{
	t_list	*alloc;
	t_list *tmp;
	t_mem	*mem;

	alloc = *arena_head();
	while (alloc)
	{

		mem = alloc->content;
		if (mem->offset ==0){
			ft_remove(mem->mempool);
			free(mem);
			if (!tmp){
				*arena_head()=alloc->next;
			}
			else{
				tmp->next = alloc->next;
			}
			free(alloc);
		}
		tmp = alloc;
		alloc = alloc->next;
	}
	return (1);
}

void	*ft_calloc(size_t size)
{
	void	*ptr;
	t_mem	*alloc;

	if (size <= 64)
	{
		alloc = (t_mem *)ft_lstlast(*arena_head())->content;
		if (alloc->offset + size > alloc->size)
			alloc = realloc_arena();
		ptr = alloc->mempool + alloc->offset;
		alloc->offset += size;
		return (ptr);
	}
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	ft_bzero_(ptr, size);
	if (!add_garb(ptr))
		return (free(ptr), NULL);
	return (ptr);
}
