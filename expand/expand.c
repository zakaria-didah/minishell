#include "../main.h"

char	*handel_dollar(int *i, char *input)
{
	int		start;
	char	tmp;
	char	*res;

	start = 0;
	start = (*i);
	if (ft_isdigit(input[(*i)++])){
		return NULL;
	}
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

char	*field_spliting(char *arg)
{
	int		i;
	int		field;
	char	*ifs;

	i = 0;
	field = 1;
	ifs = get_ifs();
	while (arg[i])
	{
		if (arg[i] && (arg[i] == SEP || arg[i] == SEP2))
		{
			field = arg[i++];
			while (arg[i] && arg[i] != field)
				i++;
			i++;
		}
		while (arg[i] && (arg[i] != SEP && arg[i] != SEP2))
		{
			if (is_in(arg[i], ifs))
				arg[i] = 127;
			i++;
		}
	}
	return (arg);
}

char	*expand_var(char *arg, int *i)
{
	int		start;
	char	*expande;

	start = ++(*i);
	expande = handel_dollar(i, arg);
	if (expande){
		arg = ft_strinsert(arg, expande, start, *i);
		*i = (start-1) + ft_strlen(expande)-1;
	}
	else
	{
		ft_bzero(arg + start - 1, *i - start + 1);
		ft_memmove(arg + start - 1, arg + (*i), ft_strlen(arg + *i) + 1);
		*i = start - 1;
	}
	return (arg);
}

char	*expand_vars(char *arg)
{
	int	i;
	int	q;

	q = 1;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == SEP || arg[i] == SEP2)
		{
			if (arg[i] == SEP)
				skip_quote(arg, &i);
			else
				q = !q;
		}
		if (arg[i] == '$' && (arg[i + 1] && ft_isalnum(arg[i + 1])))
		{
			arg = expand_var(arg, &i);
			if (q)
				arg = field_spliting(arg);
		}
		else if (arg[i] == '$' && arg[i + 1] == '?')
			arg = ft_strinsert(arg, ft_itoa(var->exit_s), i+1, i + 2);
		i++;
	}
	return (arg);
}

char	**expand(char *arg)
{
	char	**res;

	res = NULL;
	ft_striteri(arg, &sep);
	arg = expand_vars(arg);
	res = ft_split(arg, (char[2]){127, 0});
	res = check_wildcard(res);
	res = quet_remove(res);
	return (res);
}
