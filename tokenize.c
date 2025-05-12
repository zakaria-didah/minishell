/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:03:05 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/12 14:03:37 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	handel_redin(char *input, int *i, t_token *token)
{
	if (input[*i + 1] && input[*i + 1] == '<')
	{
		token->type = HDOC;
		token->value = ft_strdup("<<");
		(*i) += 2;
	}
	else
	{
		token->type = RED_IN;
		token->value = ft_strdup("<");
		(*i)++;
	}
}

void	handel_redout(char *input, int *i, t_token *token)
{
	if (input[*i + 1] && input[*i + 1] == '>')
	{
		token->type = APPEND;
		token->value = ft_strdup(">>");
		(*i) += 2;
	}
	else
	{
		token->type = RED_OUT;
		token->value = ft_strdup(">");
		(*i)++;
	}
}

void	handel_word(char *input, int *i, t_token *token)
{
	int		start;
	char	quot;

	start = *i;
	while (input[*i] && !ft_strchr("\t\n |<>", input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			quot = input[*i];
			(*i)++;
			while (input[*i] != quot)
				(*i)++;
		}
		(*i)++;
	}
	token->type = WORD;
	token->value = ft_substr(input, start, *i - start);
}

t_list	*tokenize(char *input)
{
	t_token	*token;
	t_list	*head;
	int		i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		token = ft_calloc(sizeof(t_token), C_ARENA);
		if (input[i] == '|')
		{
			token->type = PIPE;
			i++;
		}
		else if (input[i] == '<')
			handel_redin(input, &i, token);
		else if (input[i] == '>')
			handel_redout(input, &i, token);
		else
			handel_word(input, &i, token);
		ft_lstadd_back(&head, ft_lstnew(token));
	}
	return (head);
}
