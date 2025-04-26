#include "libft.h"

void	ft_arrdel(char **arr, int elem)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arr[i])
	{
		if (i == elem)
		{
			ft_memmove(arr + i, arr + i + 1, (ft_arrlen(arr) - i)
				* sizeof(char *));
			break ;
		}
		i++;
	}
}
