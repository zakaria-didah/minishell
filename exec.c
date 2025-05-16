/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:25:26 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/16 18:12:04 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "exec.h"

pid_t	fork_cmd(void)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (throw_error("fork failed\n"), -1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	return (pid);
}

int	exec_child(char **args)
{
	char	*path;
	int		stat;

	if (!args || !args[0])
	{
		ft_free();
		exit(SUCCESS);
	}
	g_var->curr_cmd = args[0];
	path = find_cmd(args[0]);
	if (!path)
	{
		stat = g_var->exit_s;
		ft_free();
		exit(stat);
	}
	execve(path, args, envtoarr());
	ft_putendl_fd("shit happend", 2);
	perror(path);
	ft_free();
	exit(errno);
}

pid_t	exec_cmd(t_list *cmd)
{
	pid_t	pid;

	pid = fork_cmd();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (redirect(cmd) < 0)
			(ft_free(), exit(ERROR));
		exec_child(((t_cmd *)cmd->content)->args);
	}
	else
		wait_for_it(pid, pid, 1);
	return (pid);
}

void	execute(t_list *cmd_lst)
{
	if (ft_lstsize(cmd_lst) > 1)
		pipex(cmd_lst);
	else
	{
		if (((t_cmd *)cmd_lst->content)->args && !exec_builtin(cmd_lst, 1))
			exec_cmd(cmd_lst);
	}
}
