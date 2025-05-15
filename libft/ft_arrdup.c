/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:57:09 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/14 11:38:10 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garb.h"
#include "libft.h"

char	**ft_arrdup(char **arr)
{
	int		i;
	char	**res;

	i = 0;
	if (!arr)
		return (NULL);
	res = ft_calloc((ft_arrlen(arr) + 1) * sizeof(char *), C_TRACK);
	while (arr[i])
	{
		res[i] = ft_strdup(arr[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}
