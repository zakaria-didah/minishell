/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:26:09 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/17 00:24:48 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "main.h"
# include <signal.h>

void	signal_handler(int sig);

void	default_signal(void);

void	sig_heredoc(int sig);
#endif
