/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:25:59 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/15 10:26:00 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	wait_for_it(pid_t pid, pid_t lastpid, int count)
{
	int		i;
	pid_t	res;
	int		stat;

	i = 0;
	while (i < count)
	{
		res = waitpid(pid, &stat, 0);
		if (res == lastpid)
		{
			if (WIFEXITED(stat))
				g_var->exit_s = WEXITSTATUS(stat);
			else if (WIFSIGNALED(stat))
				g_var->exit_s = WTERMSIG(stat) + 128;
			else
				g_var->exit_s = ERROR;
		}
		i++;
	}
	g_var->child = false;
	if (g_var->exit_s == 130)
		write(1, "\n", 1);
	else if (g_var->exit_s == 131)
		write(1, "Quit (core dumped)\n", 20);
}

void	pipe_it(int prev_fd, t_list *head, int fd[2])
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (head->next)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (redirect(head) < 0)
		exit(ERROR);
	if (!exec_builtin(head))
		exec_child(((t_cmd *)head->content)->args);
	else
		exit(g_var->exit_s);
}

int	check_next_pipe(t_list *head)
{
	t_token	*tok;

	if (head->next)
	{
		tok = head->next->content;
		if (!(tok->type == WORD || tok->type == RED_IN || tok->type == RED_OUT
				|| tok->type == APPEND || tok->type == HDOC))
		{
			return (throw_error("syntax error near unexpected token `|'"),
				ERROR);
		}
	}
	else
	{
		return (throw_error("syntax error near unexpected token `|'"), ERROR);
	}
	return (SUCCESS);
}

int	pipex(t_list *head)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;
	int		i;

	prev_fd = -1;
	i = 0;
	while (head)
	{
		if (head->next && pipe(fd) < 0)
			return (perror("pipe"), -1);
		pid = fork_cmd();
		if (pid < 0)
			return (g_var->exit_s = -1, -1);
		else if (pid == 0)
			pipe_it(prev_fd, head, fd);
		if (prev_fd != -1)
			close(prev_fd);
		if (head->next)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		head = head->next;
		i++;
	}
	return (wait_for_it(-1, pid, i), 0);
}
