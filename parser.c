// #include "parser.h"
#include "main.h"

/*--->Some func's to debug<---*/
/*⇓⇓⇓⇓ print_list ⇓⇓⇓⇓*/
void	pl(t_list *head)
{
	t_list	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("value -> [%s]\n", ((t_token *)tmp->content)->value);
		tmp = tmp->next;
	}
}

/*⇓⇓⇓⇓ print_array ⇓⇓⇓⇓*/
void	parr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("[%s]\n", arr[i++]);
	}
}

/*
to handel the wildcard * in the input string.
Not fully ready yet.
*/
t_bool	wildcard(char *txt, char *pat)
{
	char	*buffer;

	int(n), (m), (i), (j), (startIndex), (match);
	buffer = malloc(1000);
	i = 0;
	j = 0;
	match = 0;
	startIndex = -1;
	n = ft_strlen(txt);
	m = ft_strlen(pat);
	while (i < n)
	{
		if (j < m && pat[j] == txt[i])
		{
			i++;
			j++;
		}
		else if (j < m && (pat[j] == '*'))
		{
			startIndex = j;
			match = i;
			j++;
		}
		else if (startIndex != -1)
		{
			j = startIndex + 1;
			match++;
			i = match;
		}
		else
			return (FALSE);
	}
	while (j < m && pat[j] == '*')
		j++;
	if (j == m)
		return ;
	return (TRUE);
}
/*
it tokenize the input string and return a list of tokens
it may look over complicated but it's just a simple tokenizer
i know it's not readdable but i will fix it later...
*/

char	*handel_dollar(int *i, char *input)
{
	int		start;
	char	tmp;
	char	*res;

	start = 0;
	start = ++(*i);
	while ((isalnum(input[*i]) || input[*i] == '_'))
	{
		(*i)++;
	}
	tmp = input[*i];
	input[*i] = 0;
	res = getenv(input + start);
	input[*i] = tmp;
	return (res);
}

t_list	*tokenize(char *input)
{
	t_token	*token;
	t_list	*head;
	int		i;
	int		j;
	int		start;
	char	quote;
	char	*expand;

	head = NULL;
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == ' ')
		{
			i++;
			continue ;
		}
		token = ft_calloc(sizeof(t_token));
		if (input[i] == '|')
		{
			token->type = PIPE;
			token->value = ft_strdup("|");
		}
		else if (input[i] == '<')
		{
			if (input[i + 1] && input[i + 1] == '<')
			{
				token->type = HDOC;
				token->value = ft_strdup("<<");
				i++;
			}
			else
			{
				token->type = RED_IN;
				token->value = ft_strdup("<");
			}
		}
		else if (input[i] == '>')
		{
			if (input[i + 1] && input[i + 1] == '>')
			{
				token->type = APPEND;
				token->value = ft_strdup(">>");
				i++;
			}
			else
			{
				token->type = RED_OUT;
				token->value = ft_strdup(">");
			}
		}
		else if (input[i] == '$')
		{
			token->type = DOLLAR;
			expand = handel_dollar(&i, input);
			if (!expand)
				expand = ft_strdup("");
			token->value = expand;
		}
		else if (input[i] == '"')
		{
			quote = input[i++];
			start = i;
			while (input[i] && input[i] != quote)
			{
				if (input[i] == '$')
				{
					token->value = ft_strjoin(token->value, ft_substr(input,
								start, i - start));
					token->value = ft_strjoin(token->value, handel_dollar(&i,
								input));
					start = i;
					i--;
				}
				i++;
			}
			token->type = DQUOTE;
			token->value = ft_strjoin(token->value, ft_substr(input, start, i
						- start));
			i++;
		}
		else if (input[i] == '\'')
		{
			quote = input[i++];
			start = i;
			while (input[i] && input[i] != quote)
				i++;
			token->type = SQUOTE;
			token->value = ft_substr(input, start, i - start);
			i++;
		}
		else
		{
			start = i;
			while (input[i] && !strchr(" |<>$", input[i]))
				i++;
			token->type = WORD;
			token->value = ft_substr(input, start, i - start);
		}
		ft_lstadd_back(&head, ft_lstnew(token));
	}
	return (head);
}

/*
this shit is experimental...
*/

t_list	*parse(t_list *tokens)
{
	t_token	*token;
	t_cmd	*cmd;
	t_list	*cmd_lst;
	int		ac;

	cmd_lst = NULL;
	ac = 0;
	while (tokens)
	{
		cmd = ft_calloc(sizeof(t_cmd));
		cmd->args = ft_calloc(sizeof(char *) * (ft_lstsize(tokens) + 1));
		token = tokens->content;
		while (tokens && token && token->type != PIPE)
		{
			token = tokens->content;
			if (token->type == WORD || token->type == DOLLAR
				|| token->type == DQUOTE || token->type == SQUOTE)
			{
				cmd->args[ac++] = ft_strdup(token->value);
			}
			else if (token->type == RED_IN)
			{
				if (tokens->next)
				{
					tokens = tokens->next;
					token = tokens->content;
					if (token->type == WORD || token->type == DOLLAR
						|| token->type == DQUOTE || token->type == SQUOTE)
					{
						cmd->in = ft_strdup(token->value);
					}
					else
					{
						throw_error(NULL);
					}
				}
				else
				{
					throw_error(NULL);
				}
			}
			else if (token->type == RED_OUT)
			{
				if (tokens->next)
				{
					tokens = tokens->next;
					token = tokens->content;
					if (token->type == WORD || token->type == DOLLAR
						|| token->type == DQUOTE || token->type == SQUOTE)
					{
						cmd->out = ft_strdup(token->value);
					}
					else
					{
						throw_error(NULL);
					}
				}
				else
				{
					throw_error(NULL);
				}
			}
			else if (token->type == APPEND)
			{
				if (tokens->next)
				{
					tokens = tokens->next;
					token = tokens->content;
					if (token->type == WORD || token->type == DOLLAR
						|| token->type == DQUOTE || token->type == SQUOTE)
					{
						cmd->out = ft_strdup(token->value);
						cmd->append = TRUE;
					}
					else
					{
						throw_error(NULL);
					}
				}
				else
				{
					throw_error(NULL);
				}
			}
			else if (token->type == HDOC)
			{
				if (tokens->next)
				{
					tokens = tokens->next;
					token = tokens->content;
					if (token->type == WORD || token->type == DOLLAR
						|| token->type == DQUOTE || token->type == SQUOTE)
					{
						cmd->hdoc = ft_strdup(token->value);
					}
					else
					{
						throw_error(NULL);
					}
				}
				else
				{
					throw_error(NULL);
				}
			}
			tokens = tokens->next;
		}
		cmd->args[ac] = NULL;
		ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
		// under construction
	}
	return (cmd_lst);
}

int	pass_the_input(char *line)
{
	int			i;
	int			res;
	char		*cmd;
	t_bultin	buildin[] = {{"cd", ft_cd}, {"echo", ft_echo}, {"export",
			ft_export}, {"unset", ft_unset}, {"env", ft_env}, {"exit", ft_exit},
			{NULL}};
	t_list		*head;
	t_list		*cmd_lst;
	char		*l;

	line = ft_strtrim(line, " ");
	if (!*line)
		return (SUCCESS);
	i = 0;
	head = tokenize(line);
	cmd_lst = parse(head);
	while (buildin[i].name)
	{
		cmd = ((t_cmd *)cmd_lst->content)->args[0];
		if (ft_strncmp(cmd, buildin[i].name, ft_strlen(cmd)) == 0)
		{
			var->curr_cmd = cmd;
			return (buildin[i].func(++((t_cmd *)cmd_lst->content)->args));
		}
		i++;
	}
	exec(cmd_lst);
	return (0);
}
