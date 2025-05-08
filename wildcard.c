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
			(w.i++, w.j++);
		else if (w.j < w.pat_len && (pat[w.j] == '*'))
			(w.start_index = w.j, w.match = w.i, w.j++);
		else if (w.start_index != -1)
			(w.j = w.start_index + 1, w.match++, w.i = w.match);
		else
			return (false);
	}
	while (w.j < w.pat_len && pat[w.j] == '*')
		w.j++;
	return (w.j == w.pat_len);
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
			res = ft_arradd(res, dir->d_name);
		dir = readdir(dp);
	}
	closedir(dp);
	if (!res)
		return (NULL);
	// sort_alpha(res);
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


char **check_wildcard(char **res)
{
	int i;
	int j;
	char ** wc;
	int quot;
	i = 0;
	j = 0;
	quot = 1;

	while (res[j])
	{
		while (res[j][i])
		{
			if (res[j][i] == SEP || res[j][i] == SEP2)
				quot = ~quot + 2;
			if (quot && res[j][i] == '*')
			{
				wc = wildcard(res[j]);
				if (wc)
				{
					res[j] = 0;
					res = ft_arrjoin(res, wc);
				}
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
	return (res);

}


