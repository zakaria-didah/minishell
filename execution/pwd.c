/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obendaou <obendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 23:59:25 by obendaou          #+#    #+#             */
/*   Updated: 2025/05/16 00:07:38 by obendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	pwd(char **argv)
{
	char	*pwd;

	if (argv[0])
		return (ft_putstr_fd("minishell: pwd: no options\n", 2), -1);
	pwd = ft_getenv("PWD");
	if (!pwd)
		return (ft_putstr_fd("error retrieving current directory\n", 2), -1);
	printf("%s\n", pwd);
	return (0);
}
