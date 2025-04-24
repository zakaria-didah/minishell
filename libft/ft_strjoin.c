/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:21:30 by zdidah            #+#    #+#             */
/*   Updated: 2025/04/19 12:15:53 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	size_t s1_len = ft_strlen(s1);
	size_t s2_len = ft_strlen(s2);
	str = ft_calloc(sizeof(char) * (s1_len + s2_len + 1), C_ARENA);
	if (s1)
		ft_strlcpy(str, s1, s1_len + 1);
	if (s2)
		ft_strlcat(str, s2, s1_len + s2_len + 1);
	return (str);
}
