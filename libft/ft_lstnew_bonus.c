/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:20:01 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/16 18:37:40 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "garb.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = ft_calloc(sizeof(t_list), C_ARENA);
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}
