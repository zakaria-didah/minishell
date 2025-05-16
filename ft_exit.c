/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:25:07 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/16 22:21:19 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parser.h"

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

	status = g_var.exit_s;
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
