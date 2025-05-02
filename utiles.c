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

bool	is_balanced(char *input)
{
	ssize_t	i;
	ssize_t	j;

	__attribute__((cleanup(cleanup))) char *stack;
	stack = ft_calloc((ft_strlen(input) + 1) * sizeof(char), C_MALLOC);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '"' && (!j || stack[j - 1] == '"'))
		{
			stack[j++] = '"';
		}
		else if (input[i] == '\'' && (!j || stack[j - 1] == '\''))
		{
			stack[j++] = '\'';
		}
		if (j >= 2 && ((stack[j - 1] == '\'' && stack[j - 2] == '\'')
				|| (stack[j - 1] == '"' && stack[j - 2] == '"')))
			stack[j -= 2] = 0;
		i++;
	}
	return (j == 0);
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
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", STDOUT_FILENO);
	return (rl_clear_history(),ft_free(), exit(status), TRUE);
}

char	*join_args(char **args)
{
	int		i;
	size_t	len;
	char	*arg;

	i = 0;
	len = 0;
	if (!args[i])
		return (NULL);
	while (args[i])
		len += ft_strlen(args[i++]) + 1;
	arg = ft_calloc(len, C_ARENA);
	i = 0;
	while (args[i])
	{
		ft_strlcat(arg, args[i++], len);
		ft_strlcat(arg, " ", len);
	}
	return (arg);
}
