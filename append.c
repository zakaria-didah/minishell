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
	return (fd);
}

int	red_out(char *file)
{
	int	fd;
	int std_out;

	std_out = dup(STDOUT_FILENO);
	fd = open_file(file, RED_OUT);
	dup2(fd, STDOUT_FILENO);
	return (std_out);
}

int	red_in(char *file)
{
	int	fd;
	int std_in;

	std_in = dup(STDIN_FILENO);
	fd = open_file(file, RED_IN);
	dup2(fd, STDIN_FILENO);
	return (std_in);
}

int	append(char *file)
{
	int	fd;
	int std_out;

	std_out = dup(STDOUT_FILENO);
	fd = open_file(file, APPEND);
	dup2(fd, STDOUT_FILENO);
	return (std_out);
}
