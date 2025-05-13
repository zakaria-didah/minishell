// #include "parser.h"
#include "main.h"

/*--->Some func's to debug<---*/
/*⇓⇓⇓⇓ print_list ⇓⇓⇓⇓*/

void	pl(t_list *head, int f)
{
	t_list	*tmp;
	t_token	*token;
	t_cmd	*cmd;

	tmp = head;
	if (f == 1)
	{
		while (tmp)
		{
			cmd = (t_cmd *)tmp->content;
			parr(cmd->args);
			tmp = tmp->next;
		}
		return ;
	}
	while (tmp)
	{
		token = (t_token *)tmp->content;
		printf("value -> [%s]\n", token->value);
		tmp = tmp->next;
	}
}

/*⇓⇓⇓⇓ print_array ⇓⇓⇓⇓*/
void	parr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (void)printf("[null]\n");
	printf("{");
	while (arr[i])
	{
		printf("[%s]", arr[i++]);
		if (arr[i])
			printf(", ");
		else
			printf("}\n");
	}
}

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
				ft_lstadd_back(&cmd->in, ft_lstnew(new_red(NULL, RED_IN)));
			else
			{
				ft_lstadd_back(&cmd->in, ft_lstnew(new_red(tmp[0], RED_IN)));
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
				ft_lstadd_back(&cmd->out, ft_lstnew(new_red(NULL, RED_OUT)));
			else
				ft_lstadd_back(&cmd->out, ft_lstnew(new_red(tmp[0], RED_OUT)));
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
				ft_lstadd_back(&cmd->in, ft_lstnew(new_red(NULL, RED_IN)));
			else
				ft_lstadd_back(&cmd->out, ft_lstnew(new_red(tmp[0], APPEND)));
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
			if (file && !var->exit_s)
				ft_lstadd_back(&cmd->in, ft_lstnew(new_red(file, RED_IN)));
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
				if (!cmd->args && !cmd->in && !cmd->out)
					return (throw_error("syntax error near  token `|'"), NULL);
				break ;
			}
			tokens = tokens->next;
		}
		ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
	}
	return (cmd_lst);
}

int	check_next_pipe(t_list *head)
{
	t_token	*tok;

	if (head->next)
	{
		tok = head->next->content;
		if (!(tok->type == WORD || tok->type == RED_IN || tok->type == RED_OUT
				|| tok->type == APPEND || tok->type == HDOC))
		{
			return (throw_error("syntax error near unexpected token `|'"),
				ERROR);
		}
	}
	else
	{
		return (throw_error("syntax error near unexpected token `|'"), ERROR);
	}
	return (SUCCESS);
}

int	ft_pwd(char **argv)
{
	char	*pwd;
	char	*fre;

	if (argv[0])
		return (throw_error("pwd: no options"), FAILURE);
	fre = getcwd(NULL, 0);
	if (fre)
	{
		pwd = ft_strdup(fre);
		free(fre);
		edit_env("PWD", pwd, FALSE);
	}
	else
	{
		pwd = ft_getenv("PWD");
		if (!pwd)
			return (perror("minishell: pwd"), FAILURE);
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	return (SUCCESS);
}

int	pass_the_input(char *line)
{
	t_list	*head;
	t_list	*cmd_lst;

	line = ft_strtrim(line, " ");
	if (!*line)
		return (var->exit_s = SUCCESS);
	if (!is_balanced(line))
		return (throw_error(NULL), var->exit_s = FAILURE);
	head = tokenize(line);
	cmd_lst = parse(head);
	if (!cmd_lst)
		return (var->exit_s = FAILURE);
	execute(cmd_lst);
	return (0);
}
