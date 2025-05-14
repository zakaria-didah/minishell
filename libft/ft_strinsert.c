/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:28:28 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/14 11:38:58 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "garb.h"

char	*ft_strinsert(char *s, char *txt, int index, int end)
{
	char	*new;
	size_t	len_s;
	size_t	len_txt;

	len_s = ft_strlen(s);
	len_txt = ft_strlen(txt);
	new = ft_calloc((len_s + len_txt + 1) * sizeof(char), C_ARENA);
	ft_strlcpy(new, s, index);
	ft_strlcat(new, txt, len_s + len_txt + 1);
	ft_strlcat(new, s + end, len_s + len_txt + 1);
	return (new);
}
