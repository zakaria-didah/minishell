/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:57:06 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/14 10:57:08 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arrdel(char **arr, int elem)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (i == elem)
		{
			ft_memmove(arr + i, arr + i + 1, (ft_arrlen(arr) - i)
				* sizeof(char *));
			break ;
		}
		i++;
	}
}
