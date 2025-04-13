#include "main.h"

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

size_t	ft_atos(char *num)
{
	int		i;
	size_t	res;

	i = 0;
	res = 0;
	while (num[i] >= '0' && num[i] <= '9' && num[i])
	{
		res = res * 10 + ((num[i] - 48));
		if (res > LONG_MAX)
			return (-1);
		i++;
	}
	return (res);
}

int	ft_exit(char **args)
{
	size_t	status;
	int		i;
	char	*arg;
	size_t	len;

	status = 0;
	i = 4;
	if (args && args[0])
	{
		arg = args[0];
		if (ft_arrlen(args) > 1)
			return (throw_error("exit: too many arguments\n"), ERROR);
		while (arg[i] && isdigit(arg[i++]) == TRUE)
		{
			printf("exit: %s: numeric argument required\n", arg);
			exit(FAILURE);
		}
		status = ft_atos(arg);
		if (status < 0)
		{
			printf("exit: %s: numeric argument required\n", arg);
			exit(FAILURE);
		}
	}
	rl_clear_history();
	return (ft_putendl_fd("exit", STDOUT_FILENO), ft_free(), exit(status),
		TRUE);
}





bool	wildCard(char *txt, char *pat)
{
	int(n), (m), (i), (j), (startIndex), (match);
	i = 0;
	j = 0;
	match = 0;
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

// int	main(void)
// {
// 	char *	txt;
// 	char *	pat;

// 	txt = "baaabab";
// 	pat = "*****ba*****ab";
// 	printf("%s\n",wildCard(txt, pat) ? "true" : "false");
// }
