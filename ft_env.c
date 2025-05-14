/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:01:17 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/14 23:53:32 by zdidah           ###   ########.fr       */
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
	env = ft_calloc(sizeof(t_env), C_PARENA);
	name = split[0];
	value = split[1];
	env->name = ft_strdup(name);
	if (value)
		env->value = ft_strdup(value);
	return (env);
}

char	**envtoarr(void)
{
	int		i;
	char	**env;
	size_t	len;
	t_list	*tmp;
	int		j;

	j = 0;
	i = 0;
	len = 0;
	while (i <= BUCKET_SIZE)
	{
		len += ft_lstsize(g_var->bucket[i]);
		i++;
	}
	i = 0;
	gc_mode(C_TRACK);
	env = ft_calloc(sizeof(char *) * len, C_TRACK);
	while (i <= BUCKET_SIZE)
	{
		tmp = g_var->bucket[i];
		while (tmp)
		{
			if (((t_env *)(tmp)->content)->value)
			{
				env[j] = ft_strjoin(((t_env *)(tmp)->content)->name, "=");
				env[j] = ft_strjoin(env[j], ((t_env *)(tmp)->content)->value);
				j++;
			}
			tmp = tmp->next;
		}
		i++;
	}
	env[j] = NULL;
	gc_mode(0);
	return (env);
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

void	insert_env(char *env)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(env);
	if (len > BUCKET_SIZE - 1)
	{
		ft_lstadd_back(&g_var->bucket[BUCKET_SIZE], ft_lstnew(add_env(env)));
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

void	unset_env(char *name)
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
		if (ft_strncmp(((t_env *)(tmp->content))->name, name, len) == 0)
		{
			ft_lstremove(&g_var->bucket[len], tmp);
			return ;
		}
		tmp = tmp->next;
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
	int		i;
	size_t	len;
	t_list	*tmp;

	i = 0;
	len = ft_strlen(name);
	tmp = g_var->bucket[len];
	if (len > BUCKET_SIZE - 1)
		tmp = g_var->bucket[BUCKET_SIZE];
	gc_mode(C_PARENA);
	printf("name={%s} value=%s\n", name, value);
	while (tmp)
	{
		if (!ft_strncmp(((t_env *)(tmp->content))->name, name, len))
		{
			((t_env *)(tmp->content))->value = ft_strdup(value);
			return (gc_mode(0),printf("yes\n"), SUCCESS);
		}
		tmp = tmp->next;
	}
	name = ft_strjoin(name, "=");
	name = ft_strjoin(name, value);
	ft_lstadd_back(&g_var->bucket[len], ft_lstnew(add_env(name)));
	gc_mode(0);
	return (SUCCESS);
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
				{
					perror("Write error");
					return (ERROR);
				}
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