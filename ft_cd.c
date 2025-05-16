/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:25:13 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/16 17:20:42 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*check_path(char **args)
{
	char	*path;

	path = NULL;
	if (ft_arrlen(args) > 1)
		return (ft_strerror("too many arguments\n"), NULL);
	if (args && args[0])
		path = args[0];
	else
		return (throw_error("cd: [relative or absolute path]"), NULL);
	return (path);
}

int	ft_pwd(char **argv)
{
	char	*pwd;
	char	*fre;

	if (argv[0])
		return (throw_error("pwd: no options"), FAILURE);
	fre = getcwd(NULL, 0);
	if (fre)
	{
		pwd = ft_strdup(fre);
		free(fre);
		ft_setenv("PWD", pwd);
	}
	else
	{
		pwd = ft_getenv("PWD");
		if (!pwd)
			return (perror("minishell: pwd"), FAILURE);
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	return (SUCCESS);
}

int	ft_cd(char **args)
{
	char	*path;

	__attribute__((cleanup(cleanup))) char *tmp;
	tmp = getcwd(NULL, 0);
	if (!tmp)
		perror("getcwd");
	else
	{
		g_var->oldpwd = ft_strdup(tmp);
		free(tmp);
		tmp = NULL;
	}
	path = check_path(args);
	if (!path)
		return (ERROR);
	if (chdir(path))
		return (perror("minishell: cd"), ERROR);
	tmp = getcwd(NULL, 0);
	if (!tmp)
		(perror("cd: error retrieving current directory"));
	else
		g_var->pwd = ft_strdup(tmp);
	ft_setenv("OLDPWD", g_var->oldpwd);
	return (ft_setenv("PWD", g_var->pwd), SUCCESS);
}
