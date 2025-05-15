#include "main.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	pl(t_list *head, int f)
{
	t_list	*tmp;
	t_token	*token;
	t_cmd	*cmd;

	tmp = head;
	if (f == 1)
	{
		while (tmp)
		{
			cmd = (t_cmd *)tmp->content;
			parr(cmd->args);
			tmp = tmp->next;
		}
		return ;
	}
	while (tmp)
	{
		token = (t_token *)tmp->content;
		printf("value -> [%s]\n", token->value);
		tmp = tmp->next;
	}
}

/*⇓⇓⇓⇓ print_array ⇓⇓⇓⇓*/

/*⇓⇓⇓⇓ print_array ⇓⇓⇓⇓*/
void	parr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (void)printf("[null]\n");
	printf("{");
	while (arr[i])
	{
		printf("[%s]", arr[i++]);
		if (arr[i])
			printf(", ");
		else
			printf("}\n");
	}
}

int	gc_mode(int mode)
{
	static int	gc_mode[127] = {0};
	static int	i = 1;

	if (mode >= 0)
	{
		if (mode == 0)
		{
			if (i != 0)
				i--;
		}
		else
			gc_mode[i++] = mode;
	}
	return (gc_mode[i - 1]);
}


int main(){

	char *str = strdup("hello");

	pid_t	pid = fork();
	
	return 0;
}