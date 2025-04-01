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


void	ft_remove(void *ptr)
{
	t_garb	**head;
	t_garb	*tmp;

	head = _get_head();
	tmp = *head;
	if (tmp && tmp->ptr == ptr)
	{
		(*head) = tmp->next;
		if (*head)
			(*head)->prev = NULL;
		return (free(tmp->ptr));
	}
	while (tmp)
	{
		if (tmp->ptr == ptr)
		{
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			return (free(tmp->ptr));
		}
		tmp = tmp->next;
	}
}

t_list	**arena_head(void)
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
			{
				*arena_head() = alloc->next;
			}
			else
			{
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
	static int i= 0;
	if (size <= CHUNK)
	{
		alloc = (t_mem *)ft_lstlast(*arena_head())->content;
		if (alloc->offset + size > alloc->size)
			alloc = realloc_arena();
		ptr = alloc->mempool + alloc->offset;
		alloc->offset += size;
		return (ptr);
	}
	int fd = open("test.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	ft_putnbr_fd(i, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(size, fd);
	ft_putchar_fd('\n', fd);
	close(fd);
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size);
	if (!add_garb(ptr))
		return (free(ptr), NULL);
	return (ptr);
}
