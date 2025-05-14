#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"



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

int main(int ac, char **av, char **env)
{
	uint64_t i = 9223372036854775807;
	i+=5;
	printf("%lu\n", i);

    
}