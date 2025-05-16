/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:25:03 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/16 18:16:47 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parser.h"
#include "signals.h"

int	open_heredoc(char **file)
{
	int			fd;
	static int	id = 0;

	*file = ft_strjoin(HDOCFILE, ft_itoa(id));
	while (access(*file, F_OK) == 0)
	{
		id++;
		*file = ft_strjoin(HDOCFILE, ft_itoa(id));
	}
	fd = open(*file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	return (fd);
}

char	*remove_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = ft_calloc(ft_strlen(str) + 1, C_ARENA);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

int	is_quoted(char *input)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

void	read_heredoc(int fd, char *delemiter, bool expand)
{
	char	*line;
	size_t	len;

	len = ft_strlen(delemiter);
	while (!g_var->hdoc)
	{
		line = readline("> ");
		if (!line || (!ft_strncmp(line, delemiter, len)
				&& ft_strlen(line) == len))
		{
			free(line);
			break ;
		}
		if (expand)
			line = expand_vars(line, true);
		ft_putendl_fd(line, fd);
		if (!expand)
			free(line);
	}
	(close(fd), exit(g_var->hdoc));
}

char	*heredoc(char *delemiter)
{
	int		fd;
	char	*file;
	bool	expand;
	pid_t	pid;

	file = NULL;
	expand = 1;
	if (is_quoted(delemiter))
	{
		delemiter = remove_quotes(delemiter);
		expand = 0;
	}
	fd = open_heredoc(&file);
	if (fd < 0)
		return (NULL);
	pid = fork_cmd();
	if (pid == 0)
	{
		(signal(SIGINT, sig_heredoc), signal(SIGQUIT, SIG_IGN));
		read_heredoc(fd, delemiter, expand);
	}
	return (wait_for_it(pid, pid, 1), close(fd), file);
}
