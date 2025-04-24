#include "main.h"

int	match(char *txt, char *pat)
{
	t_wildcard	w;

	ft_bzero(&w, sizeof(t_wildcard));
	w.start_index = -1;
	w.txt_len = ft_strlen(txt);
	w.pat_len = ft_strlen(pat);
	while (w.i < w.txt_len)
	{
		if (w.j < w.pat_len && pat[w.j] == txt[w.i])
		{
			w.i++;
			w.j++;
		}
		else if (w.j < w.pat_len && (pat[w.j] == '*'))
		{
			w.start_index = w.j;
			w.match = w.i;
			w.j++;
		}
		else if (w.start_index != -1)
		{
			w.j = w.start_index + 1;
			w.match++;
			w.i = w.match;
		}
		else
			return (false);
	}
	while (w.j < w.pat_len && pat[w.j] == '*')
		w.j++;
	return (w.j == w.pat_len);
}

size_t	biglen(char **arr)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (arr[i])
	{
		if (ft_strlen(arr[i]) > len)
			len = ft_strlen(arr[i]);
		i++;
	}
	return (len);
}

void	sort_alpha(char **arr)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 1;
	while (arr[i] && arr[j])
	{
		if (ft_strncmp(arr[i], arr[j], ft_strlen(arr[i])) > 0)
		{
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
		j++;
		if (!arr[j])
		{
			i++;
			j = i + 1;
		}
	}
}

char	**wildcard(char *pat)
{
	struct dirent	*dir;
	DIR				*dp;
	char			**res;

	res = NULL;
	if (!pat)
		return (NULL);
	dp = opendir(".");
	dir = readdir(dp);
	while (dir != NULL)
	{
		if (dir->d_name[0] == '.')
		{
			dir = readdir(dp);
			continue ;
		}
		if (match(dir->d_name, pat))
		{
			res = ft_arradd(res, dir->d_name);
		}
		dir = readdir(dp);
	}
	closedir(dp);
	if (!res)
		return (NULL);
	sort_alpha(res);
	return (res);
}

char	*handel_dollar(int *i, char *input)
{
	int		start;
	char	tmp;
	char	*res;

	start = 0;
	start = (*i);
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
	{
		(*i)++;
	}
	tmp = input[*i];
	input[*i] = 0;
	res = ft_getenv(input + start);
	input[*i] = tmp;
	return (res);
}
char	*handel_dollar_(char *name)
{
	int		i;
	char	*res;

	i = 0;
	while (name[i] && (isalnum(name[i]) || name[i] == '_'))
	{
		i++;
	}
	if (i != ft_strlen(name))
		return (NULL);
	res = ft_getenv(name);
	return (res);
}

char	*get_pattren(char *arg, int start)
{
	char	*pattren;
	int		j;
	int		i;

	j = 0;
	i = start;
	while (arg[i] && (arg[i] == '*' || !isspace(arg[i])))
	{
		i++;
		j++;
	}
	i = start;
	while (i && (arg[i] == '*' || !isspace(arg[i])))
	{
		i--;
		j++;
	}
	if (i < start && !start)
		pattren = ft_substr(arg, i + 1, j);
	else
		pattren = ft_substr(arg, start, j);
	return (pattren);
}

char	**field_spliting(char *s,char **arr)
{
	char **res = ft_split(s, " \t\n");
	return (res);
}

char	*expand_vars(char *arg, token_type type)
{
	char	*expande;
	int		start;
	int		i;
	char	*tmp;
	char	**arr;
	int		feild;
	feild = 1;

	i = 0;
	if (arg[i] == '"')
		feild = ~feild+2;
	while (arg[i])
	{
		if (arg[i] == '$' && (arg[i + 1] && arg[i + 1] != '?'))
		{
			start = ++i;
			expande = handel_dollar(&i, arg);
			if (type == WORD && expande)
			{
				arr = field_spliting(expande, arr);
				// printf("%s\n", expande);
			}
			if (expande)
				arg = ft_strinsert(arg, expande, start, i);
			else
			{
				ft_bzero(arg + start - 1, i - start + 1);
				ft_memmove(arg + start - 1, arg + i, ft_strlen(arg + i) + 1);
			}
		}
		else if (arg[i + 1] != '?')
		{
			// somthing here ...
		}
		i++;
	}
	return (arg);
}

char	*quet_remove(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])	if (arg[i] == '"')
	{
		if (arg[i] == '"' || arg[i] == '\'')
		{
			ft_strlcpy(arg + i, arg + i + 1, ft_strlen(arg + i));
			i--;
		}
		i++;
	}
	return (arg);
}
char	*expand(char *arg, token_type type)
{
	int		i;
	char	*pattren;
	char	**res;

	i = 0;
	arg = quet_remove(arg);
	arg = expand_vars(arg,type);
	while (arg[i])
	{
		if (arg[i] == '*' && type == WORD)
		{
			res = wildcard(arg);
			if (res)
				arg = join_args(res);
			else
			{
				if (arg[ft_strlen(arg) - 1] == '*')
				arg[i] = 0;
			}
		}
		i++;
	}
	return (arg);
}
