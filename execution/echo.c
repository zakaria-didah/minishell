/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obendaou <obendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 23:58:58 by obendaou          #+#    #+#             */
/*   Updated: 2025/05/15 23:58:58 by obendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	echo(char **argv)
{
	int		i;
	bool	option;

	i = 0;
	option = false;
	while (argv[i] && !ft_strncmp(argv[i], "-n", 3))
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
