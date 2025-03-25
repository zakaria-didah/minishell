#include "libft/libft.h"
#include <stddef.h>

int main(){
    t_list *head = ft_lstnew("hello");
    ft_lstadd_back(&head, ft_lstnew("world"),offsetof(t_list, next) );
    ft_lstadd_back(&head, ft_lstnew("!"),offsetof(t_list, next));
    ft_lstadd_back(&head, ft_lstnew("!!\n"),offsetof(t_list, next));

    t_list *tmp = ft_lstlast(head, offsetof(t_list, next));
    printf("%s", (char *)tmp->content);
}