#include "libft.h"

char	**ft_arrdup(char **arr)
{
	int		i;
	char	**res;

	i = 0;
	if (!arr)
		return (NULL);
	res = ft_calloc((ft_arrlen(arr) + 1) * sizeof(char *), C_TRACK);
	while (arr[i])
	{
		res[i] = ft_strdup(arr[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}
