/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obendaou <obendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:57:48 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/15 23:56:34 by obendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "garb.h"

void	ft_lstremove(t_list **head, t_list *node)
{
	t_list	*prev;
	t_list	*next;
	t_list	*tmp;

	tmp = *head;
	if (!head || !node)
		return ;
	prev = NULL;
	next = (*head)->next;
	while (tmp)
	{
		if (tmp == node)
		{
			if (prev)
				prev->next = next;
			else
				*head = next;
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
		if (next)
			next = next->next;
	}
	(ft_remove(node->content), ft_remove(node));
}
