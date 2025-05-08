#include "../main.h"

int	check_is_in(char c, const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	skip_quote(char *arg, int *i)
{
	char	quot;

	quot = arg[*i];
	(*i)++;
	while (arg[*i] && arg[*i] != quot)
	{
		(*i)++;
	}
}

char	*get_ifs(void)
{
	char	*ifs;

	ifs = ft_getenv("IFS");
	if (!ifs)
		return (ft_strdup(" \t\n"));
	return (ft_strdup(ifs));
}

void	sep(unsigned int i, char *s)
{
	static int	quot = 0;

	if (*s == '\'')
	{
		if (quot == *s)
		{
			*s = SEP;
			quot = 0;
		}
		else if (quot == 0)
		{
			quot = *s;
			*s = SEP;
		}
	}
	else if (*s == '"')
	{
		if (quot == *s)
		{
			*s = SEP2;
			quot = 0;
		}
		else if (quot == 0)
		{
			quot = *s;
			*s = SEP2;
		}
	}
}

char	**quet_remove(char **arg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arg[j])
	{
		while (arg[j][i])
		{
			if (arg[j][i] == SEP || arg[j][i] == SEP2)
			{
				ft_strlcpy(arg[j] + i, arg[j] + i + 1, ft_strlen(arg[j] + i));
				i--;
			}
			i++;
		}
		j++;
		i = 0;
	}
	return (arg);
}
