/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:01:50 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/14 11:01:54 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*src = NULL;
	char		*p;
	char		*ret;
	int			i;

	p = 0;
	ret = 0;
	i = 0;
	if (str != NULL)
		src = str;
	if (src == NULL)
		return (NULL);
	p = create_word(src, delim, &i);
	if (p)
	{
		ret = p;
		src += i + 1;
	}
	return (ret);
}
