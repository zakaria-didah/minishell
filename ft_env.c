/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:52:17 by zdidah            #+#    #+#             */
/*   Updated: 2025/04/24 14:58:08 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*ft_getenv(char *name)
{
	int		i;
	char	*env;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	while (var->env[i])
	{
		if (ft_memcmp(var->env[i], name, len) == 0)
		{
			if (var->env[i][len] == '=')
			{
				env = ft_strchr(var->env[i], '=');
				if (env)
					return (ft_strdup(env + 1));
			}
		}
		i++;
	}
	return (NULL);
}

int	ft_env(char **args)
{
	int	i;

	i = 0;
	(void)args;
	while (var->env[i])
		ft_putendl_fd(var->env[i++], STDOUT_FILENO);
	return (TRUE);
}

int	edit_env(char *name, char *value, t_bool APPEND)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (var->env[i])
	{
		if (ft_strncmp(var->env[i], name, ft_strlen(name)) == 0)
		{
			gc_mode(C_TRACK);
			var->env[i] = ft_strjoin(name, value);
			return (gc_mode(0),SUCCESS);
		}
		i++;
	}
	if (APPEND)
		return (ft_setenv(name, value));
	return (gc_mode(0), FAILURE);
}

int	ft_setenv(char *name, char *value)
{
	int		i;
	size_t	len;

	if (!name)
		return (FAILURE);
	gc_mode(C_TRACK);
	if (!ft_strchr(name, '='))
		name = ft_strjoin(name, "=");
	i = 0;
	len = ft_strlen(name);
	while (var->env[i])
	{
		if (ft_memcmp(var->env[i], name, len) == 0)
		{
			var->env[i] = ft_strjoin(name, value);
			return (gc_mode(0), SUCCESS);
		}
		i++;
	}
	var->env = ft_arradd(var->env, ft_strjoin(name, value));
	return (gc_mode(0),SUCCESS);
}

int	ft_unset(char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[i])
	{
		while (var->env[j])
		{
			if (ft_strncmp(var->env[j], args[i], ft_strlen(args[i])) == 0)
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
	return (true);
}
