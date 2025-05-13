/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 22:14:02 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/13 19:22:20 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdint.h>

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
			stack[j++] = '"';
		else if (input[i] == '\'' && (!j || stack[j - 1] == '\''))
			stack[j++] = '\'';
		if (j >= 2 && ((stack[j - 1] == '\'' && stack[j - 2] == '\'')
				|| (stack[j - 1] == '"' && stack[j - 2] == '"')))
		{
			j -= 2;
			stack[j] = 0;
		}
		i++;
	}
	return (j == 0);
}

uint64_t	ft_atos(char *num)
{
	int			i;
	uint64_t	res;
	int			sign;

	sign = 1;
	if (num[0] == '-')
	{
		sign = -1;
		num++;
	}
	else if (num[0] == '+')
		num++;
	i = 0;
	res = 0;
	while (num[i] >= '0' && num[i] <= '9' && num[i])
	{
		res = (res * 10) + (num[i] - 48);
		if (res > LONG_MAX && sign == 1)
			return (UINT64_MAX);
		else if (res > (uint64_t)LONG_MAX + 1 && sign == -1)
			return (UINT64_MAX);
		i++;
	}
	return (res * sign);
}

bool	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	ft_exit(char **args)
{
	uint64_t	status;
	char		*arg;

	status = var->exit_s;
	if (args && args[0])
	{
		arg = args[0];
		if (ft_arrlen(args) > 1)
			return (throw_error("exit: too many arguments"), ERROR);
		status = ft_atos(arg);
		if (status == UINT64_MAX)
		{
			printf("exit: %s: numeric argument required\n", arg);
			status = FAILURE;
		}
		if (!is_numeric(arg))
		{
			printf("exit: %s: numeric argument required\n", arg);
			status = FAILURE;
		}
	}
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", STDERR_FILENO);
	return (rl_clear_history(), ft_free(), red_builtin(NULL), exit(status),
		TRUE);
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
