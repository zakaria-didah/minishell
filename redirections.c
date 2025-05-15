/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:26:02 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/15 13:49:58 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	open_file(char *file, int flag)
{
	int	fd;

	if (flag == APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (flag == RED_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file, O_RDONLY);
	if (fd < 0)
		perror(file);
	return (fd);
}

int	red(t_list *head)
{
	int		fd;
	t_red	*red;

	while (head)
	{
		red = (t_red *)head->content;
		if (!red->file)
			return (throw_error("ambiguous redirect"), -1);
		fd = open_file(red->file, red->type);
		if (fd < 0)
			return (fd);
		if (red->type == RED_OUT || red->type == APPEND)
			dup2(fd, STDOUT_FILENO);
		else if (red->type == RED_IN || red->type == HDOC)
			dup2(fd, STDIN_FILENO);
		close(fd);
		head = head->next;
	}
	return (SUCCESS);
}

int	redirect(t_list *head)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)head->content;
	if (cmd->red)
		if (red(cmd->red) < 0)
			return (-1);
	return (SUCCESS);
}

t_red	*new_red(char *file, t_token_type type)
{
	t_red	*red;

	red = ft_calloc(1 * sizeof(t_red), C_ARENA);
	red->file = file;
	red->type = type;
	return (red);
}

int	red_builtin(t_list *head)
{
	static int	fd = 0;
	static int	fd2 = 0;

	if (head)
	{
		fd = dup(STDOUT_FILENO);
		fd2 = dup(STDIN_FILENO);
		if (red(((t_cmd *)head->content)->red) < 0)
			return (-1);
	}
	else
	{
		dup2(fd, STDOUT_FILENO);
		dup2(fd2, STDIN_FILENO);
		close(fd);
		close(fd2);
	}
	return (SUCCESS);
}
