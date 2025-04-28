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

int	count_fields(const char *s)
{
	int		i;
	int		count;
	char	quot;

	quot = 0;
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			quot = s[i++];
			while (s[i] && s[i] != quot)
				i++;
			i++;
		}
		while (s[i] && is_in(s[i], " \t\n"))
			i++;
		if (s[i])
			count++;
		while (s[i] && (!is_in(s[i], " \t\n")))
		{
			if (s[i] == '"' || s[i] == '\'')
			{
				quot = s[i++];
				while (s[i] && s[i] != quot)
					i++;
				i++;
			}
			i++;
		}
	}
	if (quot && !count)
	{
		return (1);
	}
	return (count);
}

char	*field_spliting(char *arg)
{
	int	i;
	int	field;

	i = 0;
	field = 1;
	while (arg[i])
	{
		if (arg[i] && (arg[i] == '\'' || arg[i] == '"'))
		{
			field = arg[i++];
			while (arg[i] && arg[i] != field)
			{
				i++;
			}
			i++;
		}
		while (arg[i] && (arg[i] != '\'' && arg[i] != '"'))
		{
			if (is_in(arg[i], " \t\n"))
			{
				arg[i] = 127;
			}
			i++;
		}
	}
	return (arg);
}

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

char	**splitting(char *arg, int count)
{
	int		i;
	char	**res;
	char	qout;
	int		q;
	int		j;

	res = NULL;
	i = 0;
	qout = '"';
	res = split_(arg);
	if (res[i] && (res[i][j] && (res[i][j] != '"' || res[i][j] != '\'')))
	{
	}
	// if (check_is_in('\"', arg)<0 || check_is_in('\"', arg)<0)
	// {
	// 	printf("%s\n", arg);
	// 	res = ft_split(arg, " \t\n");
	// 	printf("res[0] = %s\n", res[0]);
	// 	return (res);
	// }
	// while (ft_arrlen(res)-1 != count)
	// {
	// 	q = check_is_in('"', arg + q);
	// 	j = check_is_in('\'', arg + q);
	// 	if (j> 0 && j < q)
	// 	{
	// 		q = j;
	// 		qout = '\'';
	// 	}
	// 	if (q<0){
	// 		res = ft_arrjoin(res, ft_split(arg+i, " \t\n"));
	// 	}
	// 	if (q > 0)
	// 		res = ft_split(ft_substr(arg, 0, q), " \t\n");
	// 	i = check_is_in(qout, arg + q + 1)+1;
	// 	if (res)
	// 		res[ft_arrlen(res)-1] = ft_strjoin(res[ft_arrlen(res)-1],
					// ft_substr(arg, q, i));
					// 	else
					// 		res= ft_arradd(res, ft_substr(arg, q, i));
					// 	q  = i ;
					// }
}

char	*expand_vars(char *arg)
{
	char	*expande;
	int		start;
	int		i;
	char	*tmp;
	char	**arr;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && (arg[i + 1] && arg[i + 1] != '?'))
		{
			start = ++i;
			expande = handel_dollar(&i, arg);
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
			if (arg[j][i] == '"' || arg[j][i] == '\'')
			{
				ft_strlcpy(arg[j] + i, arg[j] + i + 1, ft_strlen(arg[j] + i));
				i--;
			}
			i++;
		}
		j++;
	}
	return (arg);
}
char	**expand(char *arg)
{
	int		i;
	char	*pattren;
	char	**res;
	char	**wc;
	int		j;
	int		quot;
	int		fields;

	res = NULL;
	quot = 0;
	i = 0;
	j = 0;
	arg = expand_vars(arg);
	// fields = count_fields(arg);
	// printf("arg -> %s\n", arg);
	// if (fields == 1)
	// {
	// 	res = ft_arradd(res, arg);
	// }
	// else
	// {
	// 	// res = field_spliting(arg);
	// 	res = splitting(arg, fields);
	// }
	arg = field_spliting(arg);
	res = ft_split(arg, (char [2]){127, 0});
	if (!res)
		printf("error\n"), exit(1);
	while (res[j])
	{
		while (res[j][i])
		{
			if (res[j][i] == '"' || res[j][i] == '\'')
				quot = ~quot + 2;
			if (quot && res[j][i] == '*')
			{
				wc = wildcard(res[j]);
				if (wc)
					res = ft_arrjoin(res, wc);
				else
				{
					if (res[j][ft_strlen(res[j]) - 1] == '*')
						res[j][i] = 0;
				}
			}
			i++;
		}
		j++;
	}
	res = quet_remove(res);
	// printf("----res in quet_remove----\n");
	// parr(res);
	return (res);
}
