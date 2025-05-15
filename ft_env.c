/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:01:17 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/15 12:24:29 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// char	*ft_getenv(char *name)
// {
// 	int		i;
// 	char	*env;
// 	size_t	len;

// 	i = 0;
// 	if (!g_var->env || !name)
// 		return (NULL);
// 	len = ft_strlen(name);
// 	while (g_var->env[i])
// 	{
// 		if (ft_memcmp(g_var->env[i], name, len) == 0)
// 		{
// 			if (g_var->env[i][len] == '=')
// 			{
// 				env = ft_strchr(g_var->env[i], '=');
// 				if (env)
// 					return (ft_strdup(env + 1));
// 			}
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

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

char	**envtoarr(void)
{
	int		i;
	char	**env;
	size_t	j;
	t_list	*tmp;

	i = 0;
	j = calucate_len();
	gc_mode(C_TRACK);
	env = ft_calloc(sizeof(char *) * (j+1), C_TRACK);
	j = 0;
	while (i <= BUCKET_SIZE)
	{
		tmp = g_var->bucket[i];
		while (tmp)
		{
			if (((t_env *)(tmp)->content)->value)
			{
				env[j] = compine_name_value((t_env *)(tmp)->content);
				j++;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (env[j] = NULL, gc_mode(0), env);
}

// void	fill_env(char **env)
// {
// 	int	i;

// 	i = 0;
// 	gc_mode(C_PARENA | C_TRACK);
// 	while (env[i])
// 	{
// 		ft_lstadd_back(&g_var->env, ft_lstnew(add_env(env[i])));
// 		i++;
// 	}
// 	gc_mode(0);
// }

void	fill_bucket(char **env)
{
	int		i;
	char	*name;
	size_t	len;

	i = 0;
	while (env[i])
	{
		name = ft_split(env[i], "=")[0];
		len = ft_strlen(name);
		gc_mode(C_PARENA | C_TRACK);
		if (len > BUCKET_SIZE - 1)
			len = BUCKET_SIZE;
		ft_lstadd_back(&g_var->bucket[len], ft_lstnew(add_env(env[i])));
		gc_mode(0);
		i++;
	}
}

char	*ft_getenv(const char *name)
{
	int		i;
	size_t	len;
	t_list	*tmp;

	i = 0;
	len = ft_strlen(name);
	if (len > BUCKET_SIZE - 1)
		len = BUCKET_SIZE;
	tmp = g_var->bucket[len];
	while (tmp)
	{
		if (!ft_strncmp(((t_env *)(tmp)->content)->name, name, len))
			return (((t_env *)(tmp)->content)->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_setenv(char *name, char *value)
{
	size_t	len;
	t_list	*tmp;

	len = ft_strlen(name);
	tmp = g_var->bucket[len];
	if (len > BUCKET_SIZE - 1)
		tmp = g_var->bucket[BUCKET_SIZE];
	gc_mode(C_PARENA);
	while (tmp)
	{
		if (!ft_strncmp(((t_env *)(tmp->content))->name, name, len))
		{
			if (value)
				((t_env *)(tmp->content))->value = ft_strdup(value);
			return (gc_mode(0), SUCCESS);
		}
		tmp = tmp->next;
	}
	if (value)
	{
		name = ft_strjoin(name, "=");
		name = ft_strjoin(name, value);
	}
	ft_lstadd_back(&g_var->bucket[len], ft_lstnew(add_env(name)));
	return (gc_mode(0), SUCCESS);
}

int	ft_env(char **args)
{
	int		i;
	int		res;
	t_list	*tmp;

	i = 0;
	(void)args;
	res = 0;
	while (i <= BUCKET_SIZE)
	{
		tmp = g_var->bucket[i];
		while (tmp)
		{
			if (((t_env *)(tmp->content))->value)
			{
				res = printf("%s=%s\n", ((t_env *)(tmp->content))->name,
						((t_env *)(tmp->content))->value);
				if (res < 0)
					return (perror("Write error"), ERROR);
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (SUCCESS);
}
/*
int	ft_env(char **args)
{
	int	i;

	i = 0;
	(void)args;
	while (g_var->env[i])
	{
		if (ft_strchr(g_var->env[i], '='))
		{
			ft_putendl_fd(g_var->env[i], STDOUT_FILENO);
		}
		i++;
	}
	return (SUCCESS);
}

int	edit_env(char *name, char *value, t_bool APPEND)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (g_var->env[i])
	{
		if (ft_strncmp(g_var->env[i], name, ft_strlen(name)) == 0)
		{
			gc_mode(C_TRACK);
			g_var->env[i] = ft_strjoin(name, value);
			return (gc_mode(0), SUCCESS);
		}
		i++;
	}
	if (APPEND)
		return (ft_setenv(name, value));
	return (gc_mode(0), FAILURE);
}

char	*insert_env(char *name, char *value)
{
	if (!name || !value)
		return (NULL);
	if (!ft_strchr(name, '=') && value)
		name = ft_strjoin(name, "=");
	name = ft_strjoin(name, value);
	return (name);
}

int	ft_setenv(char *name, char *value)
{
	int		i;
	size_t	len;

	if (!name)
		return (FAILURE);
	gc_mode(C_TRACK);
	i = 0;
	len = ft_strlen(name);
	while (g_var->env[i])
	{
		if (ft_memcmp(g_var->env[i], name, len) == 0)
		{
			g_var->env[i] = insert_env(name, value);
			return (gc_mode(0), SUCCESS);
		}
		i++;
	}
	g_var->env = ft_arradd(g_var->env, ft_strjoin(name, value));
	return (gc_mode(0), SUCCESS);
}
*/