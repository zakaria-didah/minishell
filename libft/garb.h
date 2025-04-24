/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:32:49 by zdidah            #+#    #+#             */
/*   Updated: 2025/04/19 16:07:16 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARB_H
# define GARB_H

# include "libft.h"
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define CHUNK 64
# define ARENA_SIZE 10240
# define C_ARENA (1 << 0)
# define C_MALLOC (1 << 1)
# define C_TRACK (1 << 2)

typedef struct s_mem
{
	size_t			offset;
	size_t			size;
	char			*mempool;
}					t_mem;

typedef struct s_garb
{
	void			*ptr;
	struct s_garb	*prev;
	struct s_garb	*next;
}					t_garb;

void				ft_remove(void *ptr);
void				_link_list(t_garb *node);
t_garb				**_get_head(void);
void				*add_garb(void *ptr);
void				*ft_calloc(size_t size, int cflag);
void				ft_free(void);
size_t				list_len_(t_garb *head);
t_list				**arena_head(void);
t_mem				*realloc_arena(void);
void				dealloc_arena(void);

#endif
