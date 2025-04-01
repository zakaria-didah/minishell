/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garb_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:20:55 by zdidah            #+#    #+#             */
/*   Updated: 2025/02/02 10:35:41 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garb.h"

size_t	list_len_(t_garb *head)
{
	size_t	i;

	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
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
