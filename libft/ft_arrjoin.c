/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:57:12 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/14 11:38:00 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garb.h"
#include "libft.h"

char	**ft_arrjoin(char **arr1, char **arr2)
{
	size_t	i;
	size_t	j;
	size_t	len1;
	size_t	len2;
	char	**res;

	i = 0;
	j = 0;
	len1 = ft_arrlen(arr1);
	len2 = ft_arrlen(arr2);
	if ((!arr1 && !arr2) || (!len1 && !len2))
		return (NULL);
	res = ft_calloc((len1 + len2 + 1) * sizeof(char *), C_TRACK);
	if (arr1)
		while (arr1[i])
			res[j++] = ft_strdup(arr1[i++]);
	i = 0;
	if (arr2)
		while (arr2[i])
			res[j++] = ft_strdup(arr2[i++]);
	res[j] = 0;
	return (res);
}
