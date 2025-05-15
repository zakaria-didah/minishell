#include "../main.h"

int	env(char **argv)
{
	int	i;

	i = 0;
	if (argv[0])
		return (ft_putstr_fd("minishell: env: too many argument\ns", 2), FAILURE);
	if (argv[0][0] == '-')
		return (ft_putstr_fd("minishell: env: no options\n", 2), FAILURE);
	while (var->env[i])
	{
		printf("%s\n", var->env[i]);
		i++;
	}
	return (SUCCESS);
}