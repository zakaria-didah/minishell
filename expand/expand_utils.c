/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:42:22 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/14 10:43:26 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	skip_quote(char *arg, int *i)
{
	char	quot;

	quot = arg[*i];
	(*i)++;
	while (arg[*i] && arg[*i] != quot)
	{
		(*i)++;
	}
}

char	*get_ifs(void)
{
	char	*ifs;

	ifs = ft_getenv("IFS");
	if (!ifs)
		return (ft_strdup(" \t\n"));
	return (ft_strdup(ifs));
}

void	swap_(char *s, int *quote, int i, int j)
{
	*s = i;
	*quote = j;
}

void	sep(unsigned int i, char *s)
{
	static int	quot = 0;

	(void)i;
	if (*s == '\'')
	{
		if (quot == *s)
			swap_(s, &quot, SEP, 0);
		else if (quot == 0)
			swap_(s, &quot, SEP, *s);
	}
	else if (*s == '"')
	{
		if (quot == *s)
		{
			*s = SEP2;
			quot = 0;
		}
		else if (quot == 0)
		{
			quot = *s;
			*s = SEP2;
		}
	}
}

char	**quet_remove(char **arg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arg[j])
	{
		while (arg[j][i])
		{
			if (arg[j][i] == SEP || arg[j][i] == SEP2)
			{
				ft_strlcpy(arg[j] + i, arg[j] + i + 1, ft_strlen(arg[j] + i));
				i--;
			}
			i++;
		}
		j++;
		i = 0;
	}
	return (arg);
}
