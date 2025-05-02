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
		ft_putstr_fd(strerror(errno), 2), exit(FAILURE);
	return (fd);
}


t_red	*new_red(char *file, token_type type)
{
	t_red	*red;

	red = ft_calloc(1 *sizeof(t_red), C_ARENA);
	red->file = file;
	red->type = type;
	return (red);
}

void	red_out(t_list *head)
{
	int	fd;
	while(head)
	{
		t_red *red = (t_red *)head->content;
		fd = open_file(red->file, RED_OUT);
		dup2(fd, STDOUT_FILENO);
		head = head->next;
	}

}

void	red_in(t_list *head)
{
	int	fd;
	while(head)
	{
		t_red *red = (t_red *)head->content;
		fd = open_file(red->file, RED_IN);
		dup2(fd, STDIN_FILENO);
		head = head->next;
	}
}

void	append(t_list *head)
{
	int	fd;

	while(head)
	{
		t_red *red = (t_red *)head->content;
		fd = open_file(red->file, RED_OUT);
		dup2(fd, STDOUT_FILENO);
		head = head->next;
	}
}
