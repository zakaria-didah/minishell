#include "main.h"

void	ft_strerror(char *s)
{
	size_t	len;
	char	prefix[ft_strlen(var->curr_cmd) + 3];
	len = ft_strlen(var->curr_cmd) + 3;
	ft_strlcpy(prefix, var->curr_cmd, len);
	ft_strlcat(prefix, ": ", len);
	ft_putstr_fd(prefix, STDERR_FILENO);
	if (s)
		ft_putstr_fd(s, STDERR_FILENO);
	else
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void ft_error(char *s){
    if (!s)
        s = strerror(errno);
    dealloc_arena();
    ft_free();
    ft_putendl_fd(s, STDERR_FILENO);
    exit(1);
}


void	throw_error(char *line)
{
	char	prefix[] = "minishell: ";

	if (line)
	{
		ft_putstr_fd(prefix, 2);
		ft_putendl_fd(line, 2);
		return ;
	}
	ft_putstr_fd("minishell: syntax error\n", 2);
}

