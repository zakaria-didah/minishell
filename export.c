#include "main.h"

int	export_append(char *arg, int i)
{
	int		j;
	char	*name;
	char	*value;
	char	*old;

	j = 0;
	value = NULL;
	name = ft_substr(arg, 0, i - 1);
	if (arg[i] == '=')
		i++;
	else
		return (throw_error("there is an invalid identifier\n"), ERROR);
	value = arg + i;
	old = ft_getenv(name);
	if (old)
	{
		value = ft_strjoin(old, value);
	}
	return (ft_setenv(name, value), SUCCESS);
}

int	export_asign(char *arg, int i)
{
	char	*value;
	char	*name;

	if (arg[i] == '=')
	{
		value = arg + ++i;
		name = ft_substr(arg, 0, i);
		return (ft_setenv(name, value), SUCCESS);
	}
	else if (arg[i] == 0)
	{
		name = ft_substr(arg, 0, i);
		value = ft_getenv(name);
		if (!value)
			return (ft_setenv(name, value), SUCCESS);
	}
	else
		return (throw_error("there is an invalid identifier\n"), ERROR);
	return (SUCCESS);
}

int	ft_export(char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	parr(args);
	if (!args || !args[0])
	{
		while (var->env[i])
			ft_putendl_fd(var->env[i++], STDOUT_FILENO);
		return (SUCCESS);
	}
	while (args[i])
	{
		while (args[i][j] && ft_isalnum(args[i][j]))
			j++;
		if (args[i][j] == '+')
			return (export_append(args[i], j++));
		else
			return (export_asign(args[i], j));
		j = 0;
		i++;
	}
	return (SUCCESS);
}
