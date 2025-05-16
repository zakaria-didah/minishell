/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:32:49 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/16 16:34:46 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARB_H
# define GARB_H

# include "libft.h"
# include <errno.h>

# define CHUNK 64
# define ARENA_SIZE 1024

# define C_ARENA 0x01
# define C_PARENA 0x02
# define C_MALLOC 0x04
# define C_TRACK 0x08

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
t_mem				*realloc_arena(t_list *head);
void				dealloc_arena(void);
void				reset_arena(void);
int					clear_arena(t_list *alloc);
int					gc_mode(int mode);
t_list				**parena_head(void);

#endif
