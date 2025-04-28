/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:20:47 by zdidah            #+#    #+#             */
/*   Updated: 2025/04/19 12:16:13 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	count_them(const char *s)
{
	int		count;
	int		i;
	char	buf;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] && (s[i] == '\'' || s[i] == '"'))
		{
			buf = s[i++];
			while (s[i] && s[i] != buf)
			{
				i++;
			}
			count++;
			i++;
		}
		while (s[i] && (s[i] != '\'' && s[i] != '"'))
			i++;
		if (s[i])
			count++;
	}
	return (count);
}

char	*create_word_(const char *s)
{
	static int	j = 0;
	int			i;
	char		buf;

	i = 0;
	buf = 0;
	i = j;
	if (s[j] && (s[j] == '\'' || s[j] == '"'))
	{
		buf = s[j++];
		while (s[j] && s[j] != buf)
		{
			j++;
		}
		return (ft_substr(s, i, ++j - i));
	}
	while (s[j] && !is_in(s[j], "\"'"))
		j++;
	return (ft_substr(s, i, j - i));
}

char	**split_(const char *s)
{
	int		words_len;
	char	**words;
	int		i;

	if (!s)
		return (NULL);
	words_len = count_them(s);
	printf("%d\n", words_len);
	words = ft_calloc((words_len + 1) * sizeof(char *), C_ARENA);
	i = 0;
	while (i < words_len)
	{
		words[i] = create_word_(s);
		i++;
	}
	words[i] = NULL;
	return (words);
}
