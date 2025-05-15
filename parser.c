/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:25:52 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/15 13:43:23 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "parser.h"
#include "main.h"
#include "parser.h"
#include "signals.h"

int	parse_redin(t_list **tokens, t_cmd *cmd)
{
	t_token	*token;
	char	**tmp;

	if ((*tokens)->next)
	{
		*tokens = (*tokens)->next;
		token = (*tokens)->content;
		if (token->type == WORD)
		{
			tmp = expand(token->value);
			if (ft_arrlen(tmp) > 1 || (ft_arrlen(tmp) == 1 && tmp[0][0] == 0))
				ft_lstadd_back(&cmd->red, ft_lstnew(new_red(NULL, RED_IN)));
			else
			{
				ft_lstadd_back(&cmd->red, ft_lstnew(new_red(tmp[0], RED_IN)));
			}
		}
		else
			return (throw_error(NULL), false);
	}
	else
		return (throw_error(NULL), false);
	return (true);
}

int	parse_redout(t_list **tokens, t_cmd *cmd)
{
	t_token	*token;
	char	**tmp;

	if ((*tokens)->next)
	{
		(*tokens) = (*tokens)->next;
		token = (*tokens)->content;
		if (token->type == WORD)
		{
			tmp = expand(token->value);
			if (ft_arrlen(tmp) > 1 || (!tmp[0] || !tmp[0][0]))
				ft_lstadd_back(&cmd->red, ft_lstnew(new_red(NULL, token->type)));
			else
				ft_lstadd_back(&cmd->red, ft_lstnew(new_red(tmp[0], RED_OUT)));
		}
		else
		{
			return (throw_error(NULL), false);
		}
	}
	else
	{
		return (throw_error(NULL), false);
	}
	return (true);
}

int	parse_append(t_list **tokens, t_cmd *cmd)
{
	t_token	*token;
	char	**tmp;

	if ((*tokens)->next)
	{
		*tokens = (*tokens)->next;
		token = (*tokens)->content;
		if (token->type == WORD)
		{
			tmp = expand(token->value);
			if (ft_arrlen(tmp) > 1 || (ft_arrlen(tmp) == 1 && tmp[0][0] == 0))
				ft_lstadd_back(&cmd->red, ft_lstnew(new_red(NULL, RED_IN)));
			else
				ft_lstadd_back(&cmd->red, ft_lstnew(new_red(tmp[0], APPEND)));
		}
		else
		{
			return (throw_error(NULL), false);
		}
	}
	else
		return (throw_error(NULL), false);
	return (true);
}

int	parse_(t_list **tokens, t_cmd *cmd)
{
	t_token	*token;

	token = (*tokens)->content;
	if (token->type == WORD)
		cmd->args = ft_arrjoin(cmd->args, expand(token->value));
	else if (token->type == RED_IN)
	{
		if (!parse_redin(tokens, cmd))
			return (false);
	}
	else if (token->type == RED_OUT)
	{
		if (!parse_redout(tokens, cmd))
			return (false);
	}
	else if (token->type == APPEND)
	{
		if (!parse_append(tokens, cmd))
			return (false);
	}
	else if (token->type == HDOC)
	{
		if (!parse_heredoc(tokens, cmd))
			return (false);
	}
	return (true);
}

t_list	*parse(t_list *tokens)
{
	t_cmd	*cmd;
	t_list	*cmd_lst;

	cmd_lst = NULL;
	while (tokens)
	{
		cmd = ft_calloc(sizeof(t_cmd), C_ARENA);
		while (tokens && (t_token *)tokens->content)
		{
			if (!parse_(&tokens, cmd))
				return (NULL);
			if (((t_token *)tokens->content)->type == PIPE
				&& check_next_pipe(tokens))
				return (NULL);
			if (((t_token *)tokens->content)->type == PIPE)
			{
				tokens = tokens->next;
				if (!cmd->args && !cmd->red )
					return (throw_error("syntax error near  token `|'"), NULL);
				break ;
			}
			tokens = tokens->next;
		}
		ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
	}
	return (cmd_lst);
}
