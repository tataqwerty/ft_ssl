#include <ft_ssl.h>

static char	s_handler(char **cur, char *next, int *i, t_md5 *flags)
{
	(*cur)++;
	if (**cur)
	{
		hash_handler(ft_strdup(*cur), flags, md5_hash, md5_output);
		*cur += ft_strlen(*cur);
	}
	else if (next)
	{
		(*i)++;
		hash_handler(ft_strdup(next), flags, md5_hash, md5_output);
	}
	else
	{
		ft_printf("md5: option requires an argument -- s\n");
		usage();
	}
	return (1);
}

static char	p_handler(t_md5 *flags)
{
	char	*input_value;

	if (!flags->p)
	{
		flags->p = 1;
		input_value = read_data(0);
	}
	else
	{
		input_value = ft_strdup("");
	}
	hash_handler(input_value, flags, md5_hash, md5_output);
	return (1);
}

/*
** returns 1 if something has been outputed.
** returns 0 if nothing has been outputed.
*/

static char	dispatcher_flags(char **cur, char *next, int *i, t_md5 *flags)
{
	if (**cur == 'q')
		flags->q = 1;
	else if (**cur == 'r')
		flags->r = 1;
	else if (**cur == 'p')
		return (p_handler(flags));
	else if (**cur == 's')
		return (s_handler(cur, next, i, flags));
	else
	{
		ft_printf("md5: illegal option -- %c\n", **cur);
		usage();
	}
	return (0);
}

/*
** This function parses flags in a single argument.
**
** return values :
** 1 - something have been outputed.
** 0 - nothing have been outputed.
** -1 ~ IS_NOT_A_FLAG - argument is not a flag.
*/

static char	parse_flags_arg(char *cur, char *next, int *i, t_md5 *flags)
{
	char	flag_output;

	if (ft_strequ(cur, "--"))
	{
		(*i)++;
		return (IS_NOT_A_FLAG);
	}
	else if (*cur != '-' || !*(++cur))
		return (IS_NOT_A_FLAG);
	flag_output = 0;
	while (*cur)
	{
		flag_output |= dispatcher_flags(&cur, next, i, flags);
		if (*cur)
			cur++;
	}
	return (flag_output);
}

/*
** @param tmp - represents result of execution of parsing flags in a single argument.
*/

char		md5_parse_flags(char *av[], int ac, int *i, t_md5 *flags)
{
	char	flag_output;
	char	tmp;

	flag_output = 0;
	while (*i < ac)
	{
		tmp = parse_flags_arg(av[*i], av[*i + 1], i, flags);	//	ATTENTION.
		if (tmp == IS_NOT_A_FLAG)
			return (flag_output);
		flag_output |= tmp;
		(*i)++;
	}
	return (flag_output);
}
