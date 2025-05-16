/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obendaou <obendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:26:02 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/16 15:01:30 by obendaou         ###   ########.fr       */
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

// int	red(t_list *head)
// {
// 	int		fd;
// 	t_red	*red;

// 	while (head)
// 	{
// 		red = (t_red *)head->content;
// 		if (!red->file)
// 			return (throw_error("ambiguous redirect"), -1);
// 		fd = open_file(red->file, red->type);
// 		if (fd < 0)
// 			return (fd);
// 		if (red->type == RED_OUT || red->type == APPEND)
// 			dup2(fd, STDOUT_FILENO);
// 		else if (red->type == RED_IN || red->type == HDOC)
// 			dup2(fd, STDIN_FILENO);
// 		close(fd);
// 		head = head->next;
// 	}
// 	return (SUCCESS);
// }

int	redirect(t_list *head)
{
	t_list	*rdc_lst;
	int		fd;
	t_red	*red;

	rdc_lst = ((t_cmd *) head->content)->red;
	while (rdc_lst)
	{
		red = (t_red *)rdc_lst->content;
		if (!red->file)
			return (throw_error("ambiguous redirect"), -1);
		fd = open_file(red->file, red->type);
		if (fd < 0)
			return (fd);
		if ((red->type == RED_OUT || red->type == APPEND) \
			&& dup2(fd, STDOUT_FILENO) == -1)
			return (perror("minishell"), -1);
		else if ((red->type == RED_IN || red->type == HDOC) \
				&& dup2(fd, STDIN_FILENO) == -1)
			return (perror("minishell"), -1);
		close(fd);
		rdc_lst = rdc_lst->next;
	}
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
		if (redirect(head) < 0)
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
