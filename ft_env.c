/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:52:17 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/14 17:31:19 by zdidah           ###   ########.fr       */
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
	env = ft_calloc(sizeof(t_env), C_PARENA);
	gc_mode(C_PARENA | C_TRACK);
	split = ft_split(var, '=');
	name = split[0];
	value = split[1];
	env->name = ft_strdup(name);
	env->value = ft_strdup(value);
	gc_mode(0);
	return (env);
}

char	**envtoarr(void)
{
	int		i;
	char	**arr;
	size_t	len;

	i = 0;
	len = ft_lstsize(g_var->env);
	arr = ft_calloc(sizeof(char *) * (len + 1), C_ARENA);
	i = 0;
	while (g_var->env)
	{
		arr[i] = ft_strjoin(((t_env *)(g_var->env->content))->name, "=");
		arr[i] = ft_strjoin(arr[i], ((t_env *)(g_var->env->content))->value);
		i++;
		g_var->env = g_var->env->next;
	}
	arr[i] = NULL;
	return (arr);
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
		name = ft_split(env[i], '=')[0];
		len = ft_strlen(name);
		if (len > 24)
			len = 25;
		ft_lstadd_back(&g_var->bucket[len], ft_lstnew(add_env(env[i])));
		i++;
	}
}

void	insert_env(char *env)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(env);
	if (len > 24)
	{
		ft_lstadd_back(&g_var->bucket[25], ft_lstnew(add_env(env)));
		return ;
	}
	else
	{
		ft_lstadd_back(&g_var->bucket[len], ft_lstnew(add_env(env)));
		return ;
	}
}

void	ft_lstremove(t_list **head, t_list *node)
{
	t_list	*prev;
	t_list	*next;
	t_list	*tmp;

	tmp = *head;
	if (!head || !node)
		return ;
	prev = NULL;
	next = (*head)->next;
	while (tmp)
	{
		if (tmp == node)
		{
			if (prev)
				prev->next = next;
			else
				*head = next;
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
		if (next)
			next = next->next;
	}
}

void	unset_env(char *env)
{
	int		i;
	size_t	len;
	t_list	*tmp;

	i = 0;
	len = ft_strlen(env);
	if (len > 24)
		len = 25;
	tmp = g_var->bucket[len];
	while (tmp)
	{
		if (ft_strncmp(((t_env *)(tmp->content))->name, env, len) == 0)
		{
			ft_lstremove(&g_var->bucket[len], tmp);
			return ;
		}
		tmp = tmp->next;
	}
}

char	*get_env(const char *name)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	if (len > 24)
		len = 25;
	while ( i <= 26)
	{
		if (ft_strncmp(((t_env *)(g_var->bucket[len]->content))->name, name,
				len) == 0)
			return (((t_env *)(g_var->bucket[len]->content))->value);
		g_var->bucket[len] = g_var->bucket[len]->next;
		i++;
	}
	return (NULL);
}

int set_env(char *name, char *value)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	if (len > 24)
		len = 25;
	while (i<=26)
	{
		if (ft_strncmp(((t_env *)(g_var->bucket[len]->content))->name, name,
				len) == 0)
		{
			((t_env *)(g_var->bucket[len]->content))->value = value;
			return (SUCCESS);
		}
		g_var->bucket[len] = g_var->bucket[len]->next;
		i++;
	}
	name = ft_strjoin(name, "=");
	name = ft_strjoin(name, value);
	insert_env(name);
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