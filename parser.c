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
		return (TRUE);
	return (TRUE);
}

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
	res = ft_getenv(input + start);
	input[*i] = tmp;
	return (res);
}

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
			start = i++;
			while (input[i] && input[i] != '"')
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
			if (input[i] != '"')
				return (throw_error(NULL), NULL);
			token->type = DQUOTE;
			token->value = ft_strjoin(token->value, ft_substr(input, start, i
						- start));
			i++;
		}
		else if (input[i] == '\'')
		{
			start = i++;
			while (input[i] && input[i] != '\'')
				i++;
			if (input[i] != '\'')
				return (throw_error(NULL), NULL);
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
A func to parse the input
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

void	redirect(t_list *head)
{
	if (((t_cmd *)head->content)->out)
		red_out(((t_cmd *)head->content)->out);
	if (((t_cmd *)head->content)->append)
		append(((t_cmd *)head->content)->out);
	if (((t_cmd *)head->content)->in)
		red_in(((t_cmd *)head->content)->in);
}

int	ft_pwd(char **argv)
{
	char	*pwd;

	if (argv[0] && argv[0][0] == '-')
		return (ft_putstr_fd("minishell: pwd: no options", 1), FAILURE);
	pwd = ft_getenv("PWD");
	printf("%s\n", pwd);
	return (SUCCESS);
}

// bool	exec_buildin(t_list *cmdlst)
// {
// 	t_bultin	buildin[] = {{"cd", ft_cd}, {"echo", ft_echo}, {"export",
// 			ft_export}, {"unset", ft_unset}, {"env", ft_env}, {"exit", ft_exit},
// 			{"pwd", ft_pwd},{NULL}};
// 	char		*cmd;
// 	int			i;
// 	int			exit_stat;
// 	pid_t		child = 0;

// 	exit_stat = SUCCESS;
// 	i = 0;
// 	cmd = ((t_cmd *)cmdlst->content)->args[0];
// 	while (buildin[i].name)
// 	{
// 		if (ft_strncmp(cmd, buildin[i].name, ft_strlen(cmd)) == 0)
// 		{
// 			var->curr_cmd = cmd;
// 			if (i != 5)
// 				child = fork();
// 			if (child < 0)
// 				ft_error(NULL);
// 			if (child == 0){
// 				redirect(cmdlst);
// 				exit_stat = buildin[i].func(++((t_cmd *)cmdlst->content)->args),
// 					exit(exit_stat);
// 			}
// 			else
// 				return (wait(NULL), true);
// 		}
// 		i++;
// 	}
// 	return (FALSE);
// }
void	pipex(t_list *cmd_lst)
{

}
t_builtin	which_builtin(char **args)
{
	if (!ft_strncmp(args[0], "echo", 5))
		return (ECHO);
	else if (!ft_strncmp(args[0], "cd", 3))
		return (CD);
	else if (!ft_strncmp(args[0], "pwd", 4))
		return (PWD);
	else if (!ft_strncmp(args[0], "EXPORT", 7))
		return (EXPORT);
	else if (!ft_strncmp(args[0], "UNSET", 6))
		return (UNSET);
	else if (!ft_strncmp(args[0], "env", 4))
		return (ENV);
	else if (!ft_strncmp(args[0], "exit", 5))
		return (EXIT);
	return (NONE);
}

void	execute_command(t_cmd cmd)
{
	int	stdin_fd;
	int	stdout_fd;

	process_redirections(cmd.redirections, &stdin_fd, &stdout_fd);
}

void	exec_child(t_list *cmd)
{
	char	*path;

	redirect(cmd);
	path = find_cmd(((t_cmd *)cmd->content)->args[0]);
	execve(path, ((t_cmd *)cmd->content)->args, var->env);
}

pid_t	exec_cmd(t_list *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (throw_error("yekhkhkh"), -1);
	if (pid == 0)
		exec_child(cmd);
	return (pid);
}

void	exec_builtin(t_builtin builtin, t_list *cmd)
{
	int	std_out;
	int	std_in;

	if (((t_cmd *)cmd->content)->out)
		std_out = red_out(((t_cmd *)cmd->content)->out);
	if (((t_cmd *)cmd->content)->append)
		std_in = append(((t_cmd *)cmd->content)->out);
	if (((t_cmd *)cmd->content)->in)
		std_in = red_in(((t_cmd *)cmd->content)->in);
	if (builtin == CD)
		ft_cd(((t_cmd *)cmd->content)->args + 1);
	else if (builtin == PWD)
		ft_pwd(((t_cmd *)cmd->content)->args + 1);
	else if (builtin == ECHO)
		ft_echo(((t_cmd *)cmd->content)->args + 1);
	else if (builtin == EXPORT)
		ft_export(((t_cmd *)cmd->content)->args + 1);
	else if (builtin == UNSET)
		ft_unset(((t_cmd *)cmd->content)->args + 1);
	else if (builtin == ENV)
		ft_env(((t_cmd *)cmd->content)->args + 1);
	else
		ft_exit(((t_cmd *)cmd->content)->args + 1);
	if (((t_cmd *)cmd->content)->out)
		dup2(std_out, STDOUT_FILENO);
	if (((t_cmd *)cmd->content)->append)
		dup2(std_out, STDOUT_FILENO);
	if (((t_cmd *)cmd->content)->in)
		dup2(std_in, STDIN_FILENO);
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
		return (SUCCESS);
	i = 0;
	head = tokenize(line);
	cmd_lst = parse(head);
	if (!cmd_lst)
		return (FAILURE);
	// if (exec_buildin(cmd_lst))
	// 	return (SUCCESS);
	// exec(cmd_lst);
	execute(cmd_lst);
	return (0);
}
