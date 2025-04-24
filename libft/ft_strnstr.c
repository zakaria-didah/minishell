/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:21:56 by zdidah            #+#    #+#             */
/*   Updated: 2025/04/18 15:54:24 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*locate a substring in a string*/

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!haystack && !len)
		return (NULL);
	if (needle[0] == 0)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		while (haystack[i + j] == needle[j] && haystack[i + j] && i + j < len)
		{
			j++;
			if (needle[j] == 0)
				return ((char *)haystack + i);
		}
		i++;
		j = 0;
	}
	return (0);
}

char	*ft_revstrnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	if (len > ft_strlen(haystack))
		len = ft_strlen(haystack);
	i = len-1;
	if (!haystack && !len)
		return (NULL);
	if (needle[0] == 0)
		return ((char *)haystack);
	while (haystack[i])
	{
		while ((haystack[i + j] && haystack[i + j] == needle[j] ))
		{
			j++;
			if (needle[j] == 0)
				return ((char *)haystack + i);
		}
		i--;
		j = 0;
	}
	return (0);
}
