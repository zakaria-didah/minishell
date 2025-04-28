#include "main.h"

void heredoc(const char *delimiter)
{
    int pipefd[2];
    char *line;

    if (pipe(pipefd) < 0)
    {
        return perror("pipe"),(void)ft_exit(NULL);
    }
    size_t len = ft_strlen(delimiter);
    while (1)
    {
        line = readline("> ");
        if (!line || ft_strncmp(line, delimiter, len) == 0)
        {
            free(line);
            break;
        }
        ft_putendl_fd(line, pipefd[1]);
        free(line);
    }
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
}
