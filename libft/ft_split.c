/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:20:47 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/15 13:24:32 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "garb.h"

int	is_in(char c, const char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	count_words(const char *s, char *c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && is_in(s[i], c))
			i++;
		if (s[i])
			count++;
		while (s[i] && !is_in(s[i], c))
			i++;
	}
	return (count);
}

char	*create_word(const char *s, const char *c, int *j)
{
	int		i;
	char	*str;

	while (s[*j] && is_in(s[*j], c))
		(*j)++;
	i = *j;
	while (s[i] && !is_in(s[i], c))
		i++;
	str = ft_substr(s, *j, i - *j);
	*j = i;
	return (str);
}

char	**ft_split(const char *s, char *charset)
{
	int		words_len;
	char	**words;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	words_len = count_words(s, charset);
	words = ft_calloc((words_len + 1) * sizeof(char *), C_ARENA);
	i = 0;
	j = 0;
	while (i < words_len)
	{
		words[i] = create_word(s, charset, &j);
		i++;
	}
	words[i] = NULL;
	return (words);
}
