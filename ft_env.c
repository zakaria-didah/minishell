/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:01:17 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/17 00:19:36 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	**envtoarr(void)
{
	int		i;
	char	**env;
	size_t	j;
	t_list	*tmp;

	i = 0;
	j = calucate_len();
	gc_mode(C_TRACK);
	env = ft_calloc(sizeof(char *) * (j + 1), C_TRACK);
	j = 0;
	while (i <= BUCKET_SIZE)
	{
		tmp = g_var.bucket[i];
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

void	fill_bucket(char **env)
{
	int		i;
	char	**name;
	size_t	len;

	len = 0;
	i = 0;
	while (env[i])
	{
		while (env[i][len] != '=')
			len++;
		gc_mode(C_PARENA);
		if (len > BUCKET_SIZE - 1)
			len = BUCKET_SIZE;
		ft_lstadd_back(&g_var.bucket[len], ft_lstnew(add_env(env[i])));
		gc_mode(0);
		i++;
		len = 0;
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
	tmp = g_var.bucket[len];
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
	tmp = g_var.bucket[len];
	if (len > BUCKET_SIZE - 1)
		tmp = g_var.bucket[BUCKET_SIZE];
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
	ft_lstadd_back(&g_var.bucket[len], ft_lstnew(add_env(name)));
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
		tmp = g_var.bucket[i];
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
