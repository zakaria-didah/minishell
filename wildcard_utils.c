/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obendaou <obendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 23:11:33 by obendaou          #+#    #+#             */
/*   Updated: 2025/05/15 23:13:31 by obendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*get_pattren(char *arg, int start)
{
	char	*pattren;
	int		j;
	int		i;

	j = 0;
	i = start;
	while (arg[i] && (arg[i] == '*' || !isspace(arg[i])))
	{
		i++;
		j++;
	}
	i = start;
	while (i && (arg[i] == '*' || !isspace(arg[i])))
	{
		i--;
		j++;
	}
	if (i < start && !start)
		pattren = ft_substr(arg, i + 1, j);
	else
		pattren = ft_substr(arg, start, j);
	return (pattren);
}

char	**voo(char **res, int j)
{
	char	**wc;

	wc = wildcard(res[j]);
	if (wc)
	{
		res[j] = 0;
		res = ft_arrjoin(res, wc);
	}
	return (res);
}
