/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obendaou <obendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 23:59:21 by obendaou          #+#    #+#             */
/*   Updated: 2025/05/16 00:09:15 by obendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

bool	is_valid_name(char *name)
{
	size_t	i;

	i = 1;
	if (name == NULL || *name == '\0')
	{
		return (false);
	}
	if (!ft_isalpha(name[0]) && name[0] != '_')
	{
		return (false);
	}
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

int	arr_size(char **arr)
{
	int	size;

	size = 0;
	while (arr[size])
		size++;
	return (size);
}

void	put_sorted_env(void)
{
	char	**envcp;
	int		i;
	int		size;
	char	*tmp;

	size = arr_size(var->env);
	i = 0;
	while (i < size)
	{
		envcp[i] = var->env[i];
		i++;
	}
	envcp[i] = NULL;
	sort_alpha(envcp);
	i = 0;
	while (i < size)
	{
		tmp = envcp[i];
		while (tmp)
		{
			if (*tmp == '\"' || *tmp == '\\' || *tmp == '$' || *tmp == '`')
				ft_putchar_fd('\\', 1);
			ft_putchar_fd(*tmp, 1);
			if (*tmp == '=')
				ft_putchar_fd('\"', 1);
			tmp++;
		}
		ft_putstr_fd("\"\n", 1);
		i++;
	}
}

int	export(char **argv)
{
	char	*value;
	int		i;

	if (!argv[0])
		return (put_sorted_env(), SUCCESS);
	if (argv[0][0] == '-')
		return (ft_putstr_fd("minishell: export: no options\n", 2), FAILURE);
	while (*argv)
	{
		value = ft_strchr(*argv, '=');
		if (value)
		{
			*value = '\0';
			value++;
		}
		if (!is_valid_name(*argv))
			ft_putstr_fd("minishell: export: not a valid identifier\n", 2);
		if (is_valid_name(*argv) && value)
			i = ft_setenv(*argv, value);
		argv++;
	}
	return (SUCCESS);
}
