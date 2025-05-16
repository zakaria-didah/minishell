/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:25:34 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/16 22:23:28 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_strerror(char *s)
{
	size_t	len;
	char	*prefix;

	len = ft_strlen(g_var.curr_cmd) + 3;
	prefix = ft_calloc(sizeof(char) * len, C_ARENA);
	ft_strlcpy(prefix, g_var.curr_cmd, len);
	ft_strlcat(prefix, ": ", len);
	ft_putstr_fd(prefix, STDERR_FILENO);
	if (s)
		ft_putstr_fd(s, STDERR_FILENO);
	else
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
}


void	throw_error(char *line)
{
	char	prefix[12];

	ft_memcpy(&prefix, "minishell: ", 12);
	if (line)
	{
		ft_putstr_fd(prefix, 2);
		ft_putendl_fd(line, 2);
		return ;
	}
	ft_putstr_fd("minishell: syntax error\n", 2);
}
