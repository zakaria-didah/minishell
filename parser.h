#ifndef PARSE_H
#define PARSE_H

#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

typedef enum { false, true } bool;

t_list *parse(t_list *head);

#endif