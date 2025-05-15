#include "../main.h"

int	pwd(char **argv)
{
	char	*pwd;

	if (argv[0])
		return (ft_putstr_fd("minishell: pwd: no options\n", 2), FAILURE);
	pwd = ft_getenv("PWD");
	if (!pwd)
		return (ft_putstr_fd("minishell: pwd: error retrieving current directory", 2), FAILURE);
	printf("%s\n", pwd);
	return (SUCCESS);
}
