/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:24:53 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/16 22:21:52 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_unset(char **args)
{
	int		i;
	size_t	len;
	t_list	*tmp;

	i = 0;
	while (*args)
	{
		len = ft_strlen(*args);
		if (len > BUCKET_SIZE - 1)
			len = BUCKET_SIZE;
		tmp = g_var.bucket[len];
		while (tmp)
		{
			if (ft_strncmp(((t_env *)(tmp->content))->name, *args, len) == 0)
			{
				ft_lstremove(&g_var.bucket[len], tmp);
				return (g_var.exit_s = SUCCESS);
			}
			tmp = tmp->next;
		}
		args++;
	}
	return (g_var.exit_s = SUCCESS, SUCCESS);
}
