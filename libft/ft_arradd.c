/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arradd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 09:36:04 by zdidah            #+#    #+#             */
/*   Updated: 2025/04/25 14:46:00 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_arrlen(char **str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	**ft_arradd(char **s1, char *s2)
{
	char	**arr;
	int		i;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
	{
		arr = ft_calloc(sizeof(char *) * 2, C_ARENA);
		arr[0] = ft_strdup(s2);
		return (arr[1] = NULL, arr);
	}
	if (!s2)
		return (s1);
	arr = ft_calloc(sizeof(char *)* (ft_arrlen(s1) + 2), C_ARENA);
	while (s1 && s1[i])
	{
		arr[i] = ft_strdup(s1[i]);
		i++;
	}
	if (s2)
	{
		arr[i] = ft_strdup(s2);
		i++;
	}
	return (arr[i] = NULL, arr);
}
