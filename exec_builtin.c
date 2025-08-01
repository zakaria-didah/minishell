/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:35:13 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/17 00:17:45 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parser.h"

static t_builtins	*get_builtin(void)
{
	static t_builtins	builtin[] = {{"cd", ft_cd}, {"pwd", ft_pwd}, {"export",
		ft_export}, {"unset", ft_unset}, {"env", ft_env}, {"exit", ft_exit},
	{"echo", ft_echo}, {NULL, NULL}};

	return (builtin);
}

bool	exec_builtin(t_list *cmdlst, int apply_red)
{
	t_builtins	*builtin;
	char		*cmd;
	int			i;
	size_t		len;

	builtin = get_builtin();
	i = 0;
	cmd = ((t_cmd *)cmdlst->content)->args[0];
	len = ft_strlen(cmd);
	while (builtin[i].name)
	{
		if (!ft_strncmp(cmd, builtin[i].name, len)
			&& len == ft_strlen(builtin[i].name))
		{
			g_var.curr_cmd = cmd;
			if (apply_red == 1 && red_builtin(cmdlst) < 0)
				return (g_var.exit_s = 1, red_builtin(NULL), true);
			g_var.exit_s = builtin[i].func(++((t_cmd *)cmdlst->content)->args);
			if (apply_red == 1 && red_builtin(NULL) < 0)
				return (g_var.exit_s = 1, true);
			return (true);
		}
		i++;
	}
	return (false);
}
