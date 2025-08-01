/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:21:18 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/17 00:20:45 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "main.h"
#include "parser.h"
#include "signals.h"

t_var	g_var = {0};

char	*get_prompt(void)
{
	char	*prompt;
	char	*cwd;
	int		option;

	option = 0;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		prompt = ft_strdup(cwd);
		free(cwd);
		cwd = ft_strrchr(prompt, '/') + 1;
	}
	else
	{
		option = TRUE;
		cwd = ft_getenv("PWD");
		if (!cwd)
			cwd = ft_strdup("seriously");
	}
	if (ft_strchr(cwd, '/'))
		cwd = ft_strrchr(cwd, '/') + 1;
	prompt = ft_strjoin(cwd, "$> ");
	return (prompt);
}

int	pass_the_input(char *line)
{
	t_list	*head;
	t_list	*cmd_lst;

	line = ft_strtrim(line, " ");
	if (!*line)
		return (g_var.exit_s = SUCCESS);
	if (!is_balanced(line))
		return (throw_error(NULL), g_var.exit_s = FAILURE);
	head = tokenize(line);
	cmd_lst = parse(head);
	if (!cmd_lst)
		return (g_var.exit_s = FAILURE);
	execute(cmd_lst);
	return (0);
}

int	init(char **env)
{
	fill_bucket(env);
	__attribute__((cleanup(cleanup))) char *tmp;
	tmp = getcwd(NULL, 0);
	if (tmp)
	{
		ft_setenv("PWD", tmp);
		g_var.pwd = ft_strdup(tmp);
	}
	else
	{
		perror("minishell: error retrieving current directory");
		g_var.pwd = ft_getenv("PWD");
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void)av;
	if (ac != 1)
		return (ft_putendl_fd("minishell: no arguments", 2), FAILURE);
	init(env);
	line = NULL;
	while (true)
	{
		default_signal();
		line = readline(get_prompt());
		if (!line)
		{
			return (ft_exit(0), 0);
		}
		add_history(line);
		pass_the_input(line);
		reset_arena();
		free(line);
	}
	return (0);
}
