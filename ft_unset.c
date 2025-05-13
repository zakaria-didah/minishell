#include "main.h"


int	ft_unset(char **args)
{
	int		(i), (j);
	char	*tmp;

	i = 0;
	j = 0;
	while (args[i])
	{
		while (var->env[j])
		{
			tmp = ft_substr(var->env[j], 0, ft_strlen(args[i]));
			if (!ft_strncmp(tmp, args[i], ft_strlen(args[i])))
			{
				while (var->env[j])
				{
					var->env[j] = var->env[j + 1];
					j++;
				}
				break ;
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (SUCCESS);
}
