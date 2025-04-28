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
to handel the wildcard * in the input string.
Not fully ready yet.
*/



/*
A func to tokenize the input.
*/
t_list	*tokenize(char *input)
{
	t_token	*token;
	t_list	*head;
	int		i;
	int		j;
	int		start;
	char	*expand;
	char	quot;

	head = NULL;
	i = 0;
	j = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
		{
			i++;
			continue ;
		}
		token = ft_calloc(sizeof(t_token), C_ARENA);
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
				i+=2;
			}
			else
			{
				token->type = RED_IN;
				token->value = ft_strdup("<");
				i++;
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
				i++;
			}
		}
		else
		{
			start = i;
			while (input[i] && !ft_strchr("\t\n |<>", input[i]))
			{
				if (input[i] == '\'' || input[i] == '"')
				{
					quot = input[i++];
					while (input[i] != quot)
						i++;
				}
				i++;
			}
			token->type = WORD;
			token->value = ft_substr(input, start, i - start);
		}
		ft_lstadd_back(&head, ft_lstnew(token));
	}
	return (head);
}

/*
A func to parse the input
*/

t_list	*parse(t_list *tokens)
{
	t_token	*token;
	t_cmd	*cmd;
	t_list	*cmd_lst;
	int		ac;
	char **tmp;

	cmd_lst = NULL;
	ac = 0;
	while (tokens)
	{
		cmd = ft_calloc(sizeof(t_cmd), C_ARENA);
		cmd->args = ft_calloc(sizeof(char *) * (ft_lstsize(tokens) + 1),
				C_ARENA);
		token = tokens->content;
		while (tokens && token && token->type != PIPE)
		{
			token = tokens->content;
			if (token->type == WORD || token->type == DOLLAR
				|| token->type == DQUOTE || token->type == SQUOTE)
			{
				char **tmp = expand(token->value);
				cmd->args = ft_arrjoin(cmd->args, tmp);
				ac = ft_arrlen(cmd->args);

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
						tmp = expand(token->value);
						if (ft_arrlen(tmp) > 1 || (ft_arrlen(tmp) == 1 && tmp[0][0] == 0))
							return (throw_error("ambiguous redirect"), NULL);
						else
						{
							cmd->in = ft_strdup(tmp[0]);
						}
					}
					else
					{
						return (throw_error(NULL), NULL);
					}
				}
				else
				{
					return (throw_error(NULL), NULL);
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
						tmp = expand(token->value);
						if (ft_arrlen(tmp) > 1 || (ft_arrlen(tmp) == 1 && tmp[0][0] == 0))
							return (throw_error("ambiguous redirect"), NULL);
						else
							cmd->out = ft_strdup(tmp[0]);
					}
					else
					{
						return (throw_error(NULL), NULL);
					}
				}
				else
				{
					return (throw_error(NULL), NULL);
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
						tmp = expand(token->value);
						if (ft_arrlen(tmp) > 1 || (ft_arrlen(tmp) == 1 && tmp[0][0] == 0))
							return (throw_error("ambiguous redirect"), NULL);
						else
							cmd->out = ft_strdup(tmp[0]);
						cmd->append = TRUE;
					}
					else
					{
						return (throw_error(NULL), NULL);
					}
				}
				else
				{
					return (throw_error(NULL), NULL);
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
						return (throw_error(NULL), NULL);
					}
				}
				else
				{
					return (throw_error(NULL), NULL);
				}
			}
			tokens = tokens->next;
		}
		//cmd->args[ac] = NULL;
		ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
		// under construction
	}
	return (cmd_lst);
}
void	redirect(t_list *head)
{
	if (((t_cmd *)head->content)->out)
		red_out(((t_cmd *)head->content)->out);
	if (((t_cmd *)head->content)->append)
		append(((t_cmd *)head->content)->out);
	if (((t_cmd *)head->content)->in)
		red_in(((t_cmd *)head->content)->in);
	if (((t_cmd *)head->content)->hdoc)
		heredoc(((t_cmd *)head->content)->hdoc);
}

/*use ft_getenv("PWD") it's better
and options don't have to start with - if argv then throwerror :)*/
int	ft_pwd(char **argv)
{
	__attribute__((cleanup(cleanup))) char *pwd;
	if (argv[0] && argv[0][0] == '-')
		return (ft_putstr_fd("minishell: pwd: no options", 1), FAILURE);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("minishell: pwd"), FAILURE);
	printf("%s\n", pwd);
	return (SUCCESS);
}

bool	exec_builtin(t_list *cmdlst)
{
	t_builtins	builtin[] = {{"cd", ft_cd}, {"echo", ft_echo}, {"export",
			ft_export}, {"unset", ft_unset}, {"env", ft_env}, {"exit", ft_exit},
			{"pwd", ft_pwd}, {NULL}};
	char		*cmd;
	int			i;
	int			exit_stat;

	exit_stat = SUCCESS;
	i = 0;
	cmd = ((t_cmd *)cmdlst->content)->args[0];
	while (builtin[i].name)
	{
		if (ft_strncmp(cmd, builtin[i].name, ft_strlen(cmd) + 1) == 0)
		{
			var->curr_cmd = cmd;
			return (builtin[i].func(++((t_cmd *)cmdlst->content)->args), true);
		}
		i++;
	}
	return (false);
}
void	pipex(t_list *cmd_lst)
{
}

/* SEGV we don't check if the argv is NULL,
	plus the hash table algo is way faster,
 and it's easier for upgrading
*/
// t_builtin	exec_builtin(char **args)
// {
// 	if (!ft_strncmp(args[0], "echo", 5))
// 		return (ft_echo(args + 1), ECHO);
// 	else if (!ft_strncmp(args[0], "cd", 3))
// 		return (ft_cd(args + 1), CD);
// 	else if (!ft_strncmp(args[0], "pwd", 4))
// 		return (ft_pwd(args + 1), PWD);
// 	else if (!ft_strncmp(args[0], "EXPORT", 7))
// 		return (ft_export(args + 1), EXPORT);
// 	else if (!ft_strncmp(args[0], "UNSET", 6))
// 		return (ft_unset(args + 1), UNSET);
// 	else if (!ft_strncmp(args[0], "env", 4))
// 		return (ft_env(args + 1), ENV);
// 	else if (!ft_strncmp(args[0], "exit", 5))
// 		return (ft_exit(args + 1), EXIT);
// 	else
// 		return (NONE);
// }
/*
void	ready_to_expand(t_list *head)
{
	t_list		*tmplst;
	int			i;
	int j = 0;
	char		**arr;
	t_cmd *tmp;


	tmp = -1;
	i = 0;
	tmplst = head;
	while (tmplst)
	{
		tmp = (t_cmd *)(head->content);
		while(tmp->args[j]){
			arr = ft_split(tmp->args[j], "\"'");
			while (arr[i])
			{
				if (arr[i][0] != '\'')
				{
					if (arr[i][0] == '"')
						tmp = DQUOTE;
					arr[i] = expand(arr[i]);
				}
				i++;
			}
			j++;
		}
		tmplst = tmplst->next;
	}
}
	*/

int	pass_the_input(char *line)
{
	int		i;
	int		res;
	t_list	*head;
	t_list	*cmd_lst;
	char	*l;

	line = ft_strtrim(line, " ");
	if (!*line)
		return (SUCCESS);
	if (!is_balanced(line))
		return (throw_error(NULL), FAILURE);
	i = 0;
	head = tokenize(line);
	cmd_lst = parse(head);
	// ready_to_expand(cmd_lst);
	if (!cmd_lst)
		return (FAILURE);
	execute(cmd_lst);
	return (0);
}
