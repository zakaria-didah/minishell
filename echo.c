/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:25:37 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/15 10:47:36 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static bool	option_n(char *arg)
{
	int	i;

	if (arg[0] == '-' && arg[1] == 'n')
	{
		i = 2;
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (false);
			i++;
		}
		return (true);
	}
	return (false);
}

int	ft_echo(char **argv)
{
	int		i;
	bool	option;

	i = 0;
	option = false;
	while (argv[i] && option_n(argv[i]))
		i++;
	if (i)
		option = true;
	while (argv[i])
	{
		ft_putstr_fd(argv[i++], STDOUT_FILENO);
		if (argv[i])
			write(STDOUT_FILENO, " ", 1);
	}
	if (!option)
		write(STDOUT_FILENO, "\n", 1);
	return (SUCCESS);
}
