#include "main.h"

int	ft_exit(char *line)
{
	unsigned int	status;
	int				i;
	char			*arg;
	size_t			len;

	status = 0;
	i = 4;
	arg = strtok(line + 4, " ");
	len = ft_strlen(arg);
	while (arg[i] && isdigit(arg[i++]) == TRUE)
	{
		printf("exit: %s: numeric argument required\n", arg);
		exit(FAILURE);
	}
	if (len > 19)
	{
		printf("exit: %s: numeric argument required\n", arg);
		exit(FAILURE);
	}
	else
		status = ft_atoi(arg + 4);
	if (strtok(NULL, " ") != NULL)
		return (printf("exit: too many arguments\n"), exit(1), TRUE);
	rl_clear_history();
	return (ft_putendl_fd("exit", stdout), ft_free(), exit(status), TRUE);
}

int trow_error(char *line)
{
	char prefix[] = "minishell: ";
	if (line){
		ft_putstr_fd(prefix, 2);
		ft_putstr_fd(line, 2);
	}
	ft_putstr_fd("minishell: syntax error\n",2);
	return (FAILURE);
}

int	ft_env(char *line)
{
	int		i;
	char	**env;

	i = 0;
	env = var->env;
	while (env[i])
	{
		ft_putstr_fd(env[i], stdout);
		i++;
	}
	return (TRUE);
}

bool	wildCard(char *txt, char *pat)
{
	int	(n), (m), (i), (j), (startIndex), (match);

	i = 0;
	j = 0;
	match =0;
	startIndex = -1;
	n = ft_strlen(txt);
	m = ft_strlen(pat);
	while (i < n)
	{
		if (j < m && (pat[j] == '*' || pat[j] == txt[i]))
		{
			i++;
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
	return (j == m);
}

int	main(void)
{
	char *	txt;
	char *	pat;

	txt = "baaabab";
	pat = "*****ba*****ab";
	printf("%s\n",wildCard(txt, pat) ? "true" : "false");
}
