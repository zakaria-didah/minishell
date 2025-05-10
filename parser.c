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

/*
A func to tokenize the input.
*/

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

/*
A func to parse the input
*/

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
				return (throw_error("ambiguous redirect"), false);
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
			if (ft_arrlen(tmp) > 1 || (ft_arrlen(tmp) == 1 && tmp[0][0] == 0))
				return (throw_error("ambiguous redirect"), false);
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
				return (throw_error("ambiguous redirect"), false);
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

	if ((*tokens)->next) // Change tokens to (*tokens)
	{
		*tokens = (*tokens)->next;
		token = (*tokens)->content;
		if (token->type == WORD)
		{
			file = heredoc(token->value);
			if (file && !var->exit_s)
				ft_lstadd_back(&cmd->in, ft_lstnew(new_red(file, HDOC)));
			else {
				return false;
			}
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
	if (token->type == PIPE && check_next_pipe(*tokens) == ERROR)
		return (false);
    return (true);
}

t_list	*parse(t_list *tokens)
{
	t_token	*token;
	t_cmd	*cmd;
	t_list	*cmd_lst;

	cmd_lst = NULL;
	while (tokens)
	{
		cmd = ft_calloc(sizeof(t_cmd), C_ARENA);
		token = tokens->content;
		while (tokens && token)
		{
			token = tokens->content;
			if (!parse_(&tokens, cmd))
				return (NULL);
            if (token->type == PIPE)
            {
                tokens = tokens->next;
                if (!cmd->args && !cmd->in && !cmd->out)
                {
                    return (throw_error("syntax error near  token `|'"), NULL);
                }
                
                break;
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
		if (!(tok->type == WORD || tok->type == DOLLAR || tok->type == DQUOTE
				|| tok->type == SQUOTE))
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
	__attribute__((cleanup(cleanup))) char *pwd;
	if (argv[0])
		return (throw_error("pwd: no options"), FAILURE);
	pwd = ft_getenv("PWD");
	if (!pwd)
		pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("minishell: pwd"), FAILURE);
	printf("%s\n", pwd);
	return (SUCCESS);
}

int	pass_the_input(char *line)
{
	int		i;
	int		res;
	t_list	*head;
	t_list	*cmd_lst;
	char	*l;

	line = ft_strtrim(line, " ");
	if (!*line)
		return (var->exit_s = SUCCESS);
	if (!is_balanced(line))
		return (throw_error(NULL), var->exit_s = FAILURE);
	i = 0;
	head = tokenize(line);
	cmd_lst = parse(head);
    // pl(cmd_lst, 1);
	if (!cmd_lst)
		return (FAILURE);
	execute(cmd_lst);
	return (0);
}
