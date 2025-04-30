#include "main.h"

int	open_file(char *file, int append_redout_redin)
{
	int	fd;

	if (append_redout_redin == APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (append_redout_redin == RED_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_putstr_fd(strerror(errno), 2), exit(FAILURE);
	return (fd);
}

void	red_out(char *file)
{
	int	fd;

	fd = open_file(file, RED_OUT);
	dup2(fd, STDOUT_FILENO);
}

void	red_in(char *file)
{
	int	fd;

	fd = open_file(file, RED_IN);
	dup2(fd, STDIN_FILENO);
}

void	append(char *file)
{
	int	fd;

	fd = open_file(file, APPEND);
	dup2(fd, STDOUT_FILENO);
}
