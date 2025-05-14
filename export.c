#include "main.h"

bool is_valid_value(char *arg)
{
	int	i;

	i = 0;

	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

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
		return (throw_error("there is an invalid identifier"), ERROR);
	value = arg + i;
	old = ft_getenv(name);
	if (old)
	{
		value = ft_strjoin(old, value);
	}
	printf("name = %s\n", name);
	return (ft_setenv(name, value), SUCCESS);
}

int	export_asign(char *arg, int i)
{
	char	*value;
	char	*name;

	if (arg[i] == '=')
	{
		value = arg + (i+1);
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

char *name_of_var(char *arg, int *i)
{
	char	*name;

	if (ft_isdigit(arg[*i]))
		return NULL;
	while (arg[*i] && ft_isalnum(arg[*i]))
		(*i)++;
	name = ft_substr(arg, 0, *i);
	if (!name[0])
		return (NULL);
	return (name);
}

int	ft_export(char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!args || !args[0])
	{
		ft_putstr_fd("export: not enough arguments\n", 2);
		return (SUCCESS);
	}
	while (args[i])
	{
		if (!name_of_var(args[i], &j))
			return (throw_error("there is an invalid identifier"), ERROR);
		if (args[i][j] == '+')
			export_append(args[i], ++j);
		else 
			export_asign(args[i], j);
		j = 0;
		i++;
	}
	return (SUCCESS);
}
