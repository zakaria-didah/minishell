/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 22:14:02 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/16 18:10:37 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdint.h>

void	cleanup(void *ptr)
{
	void	*p;

	p = *(void **)ptr;
	if (p)
	{
		free(p);
		p = NULL;
	}
}

int	parse_heredoc(t_list **tokens, t_cmd *cmd)
{
	t_token	*token;
	char	*file;

	if ((*tokens)->next)
	{
		*tokens = (*tokens)->next;
		token = (*tokens)->content;
		if (token->type == WORD)
		{
			file = heredoc(token->value);
			if (file && !g_var->exit_s)
				ft_lstadd_back(&cmd->red, ft_lstnew(new_red(file, RED_IN)));
			else
				return (false);
		}
		else
			return (throw_error(NULL), false);
	}
	else
		return (throw_error(NULL), false);
	return (true);
}

bool	is_balanced(char *input)
{
	ssize_t	i;
	ssize_t	j;
	char	*stack;

	stack = ft_calloc((ft_strlen(input) + 1) * sizeof(char), C_ARENA);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '"' && (!j || stack[j - 1] == '"'))
			stack[j++] = '"';
		else if (input[i] == '\'' && (!j || stack[j - 1] == '\''))
			stack[j++] = '\'';
		if (j >= 2 && ((stack[j - 1] == '\'' && stack[j - 2] == '\'')
				|| (stack[j - 1] == '"' && stack[j - 2] == '"')))
		{
			j -= 2;
			stack[j] = 0;
		}
		i++;
	}
	return (gc_mode(0), j == 0);
}

char	*join_args(char **args)
{
	int		i;
	size_t	len;
	char	*arg;

	i = 0;
	len = 0;
	if (!args[i])
		return (NULL);
	while (args[i])
		len += ft_strlen(args[i++]) + 1;
	arg = ft_calloc(len, C_ARENA);
	i = 0;
	while (args[i])
	{
		ft_strlcat(arg, args[i++], len);
		ft_strlcat(arg, " ", len);
	}
	return (arg);
}

int	check_is_in(char c, const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
