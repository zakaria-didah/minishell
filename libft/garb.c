/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:41:16 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/15 20:19:49 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garb.h"

int	gc_mode(int mode)
{
	static int	gc_mode[127] = {0};
	static int	i = 1;

	if (mode >= 0)
	{
		if (mode == 0)
		{
			if (i != 0)
				i--;
		}
		else
			gc_mode[i++] = mode;
	}
	return (gc_mode[i - 1]);
}

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

void	*if_need_to_realloc(t_list **head, size_t size)
{
	void	*ptr;
	t_mem	*alloc;

	ptr = NULL;
	alloc = (t_mem *)ft_lstlast(*head)->content;
	if (alloc->offset + size > alloc->size)
		alloc = realloc_arena(*head);
	ptr = alloc->mempool + alloc->offset;
	alloc->offset += size;
	return (ptr);
}

void	*ft_calloc(size_t size, int cflags)
{
	void	*ptr;

	ptr = NULL;
	if (!(cflags & C_PARENA) && gc_mode(-1))
		cflags = gc_mode(-1);
	if (cflags & C_ARENA)
	{
		if (size <= CHUNK)
			return (if_need_to_realloc(arena_head(), size));
		else
			cflags = C_TRACK;
	}
	if (cflags & C_PARENA)
		return (if_need_to_realloc(parena_head(), size));
	if ((cflags & C_MALLOC) || (cflags & C_TRACK))
	{
		ptr = malloc(size);
		if (!ptr)
			return (perror("malloc"), ft_free(), exit(1), NULL);
		ft_bzero(ptr, size);
	}
	if (cflags & C_TRACK)
		add_garb(ptr);
	return (ptr);
}
