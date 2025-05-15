#include "../main.h"

int	unset(char **argv)
{
	if (!argv[0])
		return (FAILURE);
	while (*argv)
	{
		// ft_unset()
		argv++;
	}
	return (SUCCESS);
}