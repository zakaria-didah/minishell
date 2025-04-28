/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:41:16 by zdidah            #+#    #+#             */
/*   Updated: 2025/04/24 13:29:02 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garb.h"

int gc_mode(int mode)
{
	static int gc_mode = 0;

	if (mode >= 0)
		gc_mode = mode;
	return (gc_mode);

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

void	*ft_calloc(size_t size, int cflags)
{
	void	*ptr;
	t_mem	*alloc;

	ptr = NULL;
	if (!(cflags & C_PARENA) && gc_mode(-1) )
		cflags = gc_mode(-1);
	if (cflags & C_ARENA)
	{
		if (size <= CHUNK)
		{
			alloc = (t_mem *)ft_lstlast(*arena_head())->content;
			if (alloc->offset + size > alloc->size)
				alloc = realloc_arena(*arena_head());
			ptr = alloc->mempool + alloc->offset;
			alloc->offset += size;
			return (ptr);
		}
		else

			cflags = C_TRACK;
	}
	if (cflags & C_PARENA)
	{
		alloc = (t_mem *)ft_lstlast(*parena_head())->content;
		if (alloc->offset + size > alloc->size)
			alloc = realloc_arena(*parena_head());
		ptr = alloc->mempool + alloc->offset;
		alloc->offset += size;
		return (ptr);
	}
	if ((cflags & C_MALLOC) || (cflags & C_TRACK))
	{
		ptr = malloc(size);
		if (!ptr)
			return (ft_putendl_fd(strerror(errno), 2), exit(1), NULL);
		ft_bzero(ptr, size);
	}
	if (cflags & C_TRACK)
		add_garb(ptr);
	return (ptr);
}
