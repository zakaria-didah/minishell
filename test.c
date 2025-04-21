#include "main.h"

int main(int ac, char **argv)
{
	t_list 	*cmd_lst;
	t_cmdlst	*cmd;
	
	cmd_lst = NULL;
	cmd = (t_cmdlst *)ft_calloc(sizeof(t_cmdlst) * 1);
	cmd->args = (char *) ft_calloc(sizeof(char *) * 2);
	cmd->args[0] = ft_strdup("cat");
	cmd->args[1] = NULL;
	ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
	cmd = (t_cmdlst *)ft_calloc(sizeof(t_cmdlst) * 1);
	cmd->args = (char *) ft_calloc(sizeof(char *) * 2);
	cmd->args[0] = ft_strdup("echo");
	cmd->args[1] = NULL;
	ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
	cmd = (t_cmdlst *)ft_calloc(sizeof(t_cmdlst) * 1);
	cmd->args = (char *) ft_calloc(sizeof(char *) * 2);
	cmd->args[0] = ft_strdup("ech");
	cmd->args[1] = NULL;
	ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
	cmd = (t_cmdlst *)ft_calloc(sizeof(t_cmdlst) * 1);
	cmd->args = (char *) ft_calloc(sizeof(char *) * 2);
	cmd->args[0] = ft_strdup("pwd");
	cmd->args[1] = NULL;
	ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
	cmd = (t_cmdlst *)ft_calloc(sizeof(t_cmdlst) * 1);
	cmd->args = (char *) ft_calloc(sizeof(char *) * 2);
	cmd->args[0] = ft_strdup("expo");
	cmd->args[1] = NULL;
	ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
	cmd = (t_cmdlst *)ft_calloc(sizeof(t_cmdlst) * 1);
	cmd->args = (char *) ft_calloc(sizeof(char *) * 2);
	cmd->args[0] = ft_strdup("export");
	cmd->args[1] = NULL;
	ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
	execute(cmd_lst);

	while (cmd_lst)
	{
		printf("%s:  %d\n", ((t_cmdlst *)cmd_lst->content)->args[0], ((t_cmdlst *)cmd_lst->content)->type);
		cmd_lst = cmd_lst->next;
	}
}
