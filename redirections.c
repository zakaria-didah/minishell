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


int	redirect(t_list *head)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)head->content;
	if (cmd->out)
		if (red_out(cmd->out) < 0)
			return -1;
	if (cmd->in)
		if(red_in(cmd->in)<0)
			return -1;
}

t_red	*new_red(char *file, token_type type)
{
	t_red	*red;

	red = ft_calloc(1 *sizeof(t_red), C_ARENA);
	red->file = file;
	red->type = type;
	return (red);
}

int	red_out(t_list *head)
{
	int	fd;
	while(head)
	{
		t_red *red = (t_red *)head->content;
		fd = open_file(red->file, red->type);
		if (fd < 0)
			return fd;
		dup2(fd, STDOUT_FILENO);
		head = head->next;
	}

}

int	red_in(t_list *head)
{
	int	fd;
	while(head)
	{
		t_red *red = (t_red *)head->content;
		fd = open_file(red->file, RED_IN);
		if (fd < 0)
			return fd;
		dup2(fd, STDIN_FILENO);
		head = head->next;
	}
}

int red_builtin(t_list *head)
{
	static int	fd = 0;
	static int	fd2 = 0;
	if (head)
	{
		fd = dup(STDOUT_FILENO);
		fd2 = dup(STDIN_FILENO);
		if (red_out(head) < 0)
			return -1;
		if (red_in(head) < 0)
			return -1;
	}
	else
	{
		dup2(fd, STDOUT_FILENO);
		dup2(fd2, STDIN_FILENO);
		close(fd);
		close(fd2);
	}

	
}