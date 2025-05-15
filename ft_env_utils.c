/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obendaou <obendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:01:18 by obendaou          #+#    #+#             */
/*   Updated: 2025/05/15 21:05:24 by obendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*compine_name_value(t_env *env)
{
	char	*res;
	char	*name;
	char	*value;

	name = env->name;
	value = env->value;
	name = ft_strjoin(name, "=");
	res = ft_strjoin(name, value);
	ft_remove(name);
	ft_remove(value);
	return (res);
}

size_t	calucate_len(void)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (i <= BUCKET_SIZE)
	{
		len += ft_lstsize(g_var->bucket[i]);
		i++;
	}
	return (len);
}

t_env	*add_env(char *var)
{
	t_env	*env;
	char	**split;
	char	*name;
	char	*value;

	if (!var)
		return (NULL);
	split = ft_split(var, "=");
	gc_mode(C_PARENA);
	env = ft_calloc(sizeof(t_env), C_PARENA);
	name = split[0];
	value = split[1];
	env->name = ft_strdup(name);
	if (value)
		env->value = ft_strdup(value);
	gc_mode(0);
	return (env);
}
