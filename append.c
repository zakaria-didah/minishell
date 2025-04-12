#include "main.h"

int	open_file(char *file, int append_or_red)
{
	int	fd;

	if (append_or_red)
		fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0777);
	else
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
	{
		ft_putstr_fd(strerror(errno), 2), exit(FAILURE);
	}
	return (fd);
}

int	red_out(char *file)
{
	int	fd;

	fd = open_file(file, red);
	dup2(fd, STDOUT_FILENO);
	return (TRUE);
}

t_bool	append(char *file)
{
	int	fd;

	fd = open_file(file, append);
	dup2(fd, STDOUT_FILENO);
	return (TRUE);
}
