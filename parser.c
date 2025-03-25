// #include "parser.h"
#include "main.h"
/*
to handel the wildcard * in the input string.
Not fully ready yet.
*/
bool	wildcard(char *txt, char *pat)
{
	int	(n), (m), (i), (j), (startIndex), (match);
    char * buffer = malloc(1000);
	i = 0;
	j = 0;
	match =0;
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
	return ;
}
/*
it tokenize the input string and return a list of tokens
it may look over complicated but it's just a simple tokenizer
i know it's not readdable but i will fix it later...
*/
t_list *tokenize(char *input)
{
	int		i;
	t_token	*token;
    t_list 	*head;
    head = ft_calloc(sizeof(t_list));
	token = ft_calloc(sizeof(t_token));
	i = 0;
	int j = 0;
	
	while (input[i]) {
		if (input[i] == ' ') { i++; continue; }

		token = ft_calloc(sizeof(t_token));

		if (input[i] == '|') { token->type = PIPE; token->value = strdup("|"); }
		else if (input[i] == '<') { 
			if (input[i+1] == '<') { token->type = HDOC; token->value = strdup("<<"); i++; }
			else { token->type = RED_IN; token->value = strdup("<"); }
		}
		else if (input[i] == '>') { 
			if (input[i+1] == '>') { token->type = APPEND; token->value = strdup(">>"); i++; }
			else { token->type = RED_OUT; token->value = strdup(">"); }
		}
		else if (input[i] == '$') { 
			token->type = DOLLAR;
			int start = ++i;
			while (isalnum(input[i]) || input[i] == '_') i++;
			token->value = strndup(input + start, i - start);
		}
		else if (input[i] == '"' || input[i] == '\'') { 
			char quote = input[i++];
			int start = i;
			while (input[i] && input[i] != quote) i++;
			token->type = DQUOTE;
			token->value = strndup(input + start, i - start);
			i++;
		}
		else { 
			int start = i;
			while (input[i] && !strchr(" |<>$", input[i])) i++;
			token->type = WORD;
			token->value = strndup(input + start, i - start);
		}

		if (!head)
			head = token;
		else 
			ft_lstadd_back(&head, token);
		i++;
	}

	
    return head;
}

/*
this shit is experimental... 
*/

t_cmd *parse(t_list *tokens){
	t_token *token = tokens->content;
	t_cmd *cmd;
	int ac = 0;
	while (tokens){
		cmd = ft_calloc(sizeof(t_cmd));
		cmd->args = ft_calloc(sizeof(char *)*10);
		while (token->type != PIPE){
			if (token->type == WORD || token->type == DOLLAR || token->type == DQUOTE || token->type == SQUOTE )
			{
				cmd->args[ac++] = ft_strdup(token->value);
			}
			else if(token->type == RED_IN)
			{
				if (tokens->next)
				{
					tokens = tokens->next;
					token = tokens->content;
					if (token->type == WORD || token->type == DOLLAR || token->type == DQUOTE || token->type == SQUOTE )
					{
						cmd->in = ft_strdup(token->value);
					}
					else
					{
						trow_error(NULL);
					}
				}
				else
				{
					trow_error(NULL);
				}
				
			}else if ( token->type == RED_OUT)
			{
				if (tokens->next)
				{
					tokens = tokens->next;
					token = tokens->content;
					if (token->type == WORD || token->type == DOLLAR || token->type == DQUOTE || token->type == SQUOTE )
					{
						cmd->out = ft_strdup(token->value);
					}
					else
					{
						trow_error(NULL);
					}
				}
				else
				{
					trow_error(NULL);
				}
			}else if ( token->type == APPEND){
				if (tokens->next)
				{
					tokens = tokens->next;
					token = tokens->content;
					if (token->type == WORD || token->type == DOLLAR || token->type == DQUOTE || token->type == SQUOTE )
					{
						cmd->out = ft_strdup(token->value);
						cmd->append = TRUE;
					}
					else
					{
						trow_error(NULL);
					}
				}
				else
				{
					trow_error(NULL);
				}
			}else if ( token->type == HDOC){
				if (tokens->next)
				{
					tokens = tokens->next;
					token = tokens->content;
					if (token->type == WORD || token->type == DOLLAR || token->type == DQUOTE || token->type == SQUOTE )
					{
						cmd->hdoc = ft_strdup(token->value);
					}
					else
					{
						trow_error(NULL);
					}
				}
				else
				{
					trow_error(NULL);
				}
			}
			tokens = tokens->next;
		}
		cmd->args[ac] = NULL;
		cmd->next = NULL;
		//under construction

	}

	return cmd;
}


int	pass_the_input(char *line)
{
	int			i;
	t_bultin	buildin[] = *get_bin();

	line = ft_strtrim(line, " ");
	line = strtok(line, " \t\n");
	i = 0;
	while (buildin[i].name)
	{
		if (ft_strncmp(line, buildin[i].name, ft_strlen(buildin[i].name) == 0))
		{
			return (buildin[i].func(strtok(NULL, NULL)));
		}
		i++;
	}
	t_list *head = tokenize(line);
	t_cmd *cmd = parse(head);

	return (0);
}
