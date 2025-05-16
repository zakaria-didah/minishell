/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:25:20 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/16 22:16:13 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	add_slash_to_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		i++;
	}
}

char	**get_path(void)
{
	char	**path;
	char	*tmp;

	tmp = ft_getenv("PATH");
	if (!tmp)
		return (ft_strerror("command not found\n"), NULL);
	path = ft_split(tmp, ":");
	add_slash_to_path(path);
	return (path);
}

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

char	*absolute_path(char *cmd)
{
	if (access(cmd, F_OK | X_OK))
		return (perror(cmd), NULL);
	else if (is_directory(cmd))
		return (ft_strerror("is a directory\n"), g_var.exit_s = 126, NULL);
	return (cmd);
}

char	*find_cmd(char *cmd)
{
	char	*cmd_path;
	int		j;
	char	**path;

	cmd_path = cmd;
	if (ft_strchr(cmd_path, '/'))
		return (absolute_path(cmd_path));
	else
	{
		path = get_path();
		if (!path || !cmd || !*cmd)
			return (g_var.exit_s = 127, NULL);
		j = 0;
		while (path[j])
		{
			cmd_path = ft_strjoin(path[j], cmd);
			if (access(cmd_path, F_OK | X_OK) == 0)
			{
				if (!is_directory(cmd_path))
					return (cmd_path);
			}
			j++;
		}
	}
	return (ft_strerror("command not found\n"), g_var.exit_s = 127, NULL);
}
