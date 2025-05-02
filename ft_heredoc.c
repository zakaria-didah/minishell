#include "main.h"

int open_heredoc(char **file)
{
    int fd;
    static int id = 0;
    *file = ft_strjoin(HDOCFILE, ft_itoa(id));
    while(access(*file, F_OK) == 0)
    {
        id++;
        *file = ft_strjoin(HDOCFILE, ft_itoa(id));
    }
    fd = open(*file, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd < 0)
    {
        perror("open");
        return (-1);
    }
    return (fd);
}

char *remove_quotes(char *str)
{
    char *new_str;
    int i = 0;
    int j = 0;

    new_str = ft_calloc(ft_strlen(str) + 1, C_ARENA);

    if (!new_str)
        return (NULL);
    while (str[i])
    {
        if (str[i] != '\'' && str[i] != '"')
            new_str[j++] = str[i];
        i++;
    }
    new_str[j] = '\0';
    return (new_str);
}

int is_quoted(char *input)
{
    size_t i;

    i = 0;
    while (input[i])
    {
        if (input[i] == '"' || input[i] == '\'')
            return 1;
        i++;
    }
    return (0);
}

char * heredoc(t_list *head)
{
    int fd;
    char *line;
    t_red* red = (t_red *)head->content;
    char *file = NULL;
    bool expand = 1;
    pid_t pid;

    if (is_quoted(red->file))
       ( red->file = remove_quotes(red->file), expand = 0);
    fd = open_heredoc(&file);
    pid = fork_cmd();
    if (pid == -1)
        return (NULL);
    if (pid == 0){
        size_t len = ft_strlen(red->file);
        var->hdoc = 1;
        while(head){
            red = (t_red *)head->content;
            len = ft_strlen(red->file);
            while (1)
            {
                line = readline("> ");
                if (!line || (!ft_strncmp(line, red->file, len) && ft_strlen(line) == len))
                {
                    free(line);
                    break;
                }
                if (expand)
                    line = expand_vars(line);
                ft_putendl_fd(line, fd);
                if (!expand)
                    free(line);
            }
            head = head->next;
        }
        close(fd);
        exit(0);
    }else
    {
        waitpid(pid, NULL, 0);
    }
    return (file);
}
