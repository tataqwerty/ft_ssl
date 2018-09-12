#include <ft_ssl.h>

static char	*read_data(int fd)
{
	char	*line;
	char	*data;

	line = NULL;
	data = ft_strdup("");
	while (get_next_line(fd, &line) > 0)
	{
		line = ft_strjoinfree(line, "\n", 1);
		data = ft_strjoinfree(data, line, 3);
	}
	return (data);
}

static void	hash_handler(char *input_value, t_md5 *flags)
{
	char	*hashed_value;

	ft_printf("===> %s", input_value);
	// hashed_value = hash(input_value);
	// output(input_value, hashed_value, flags);
	ft_strdel(&input_value);
	// ft_memdel(&hashed_value);
}

static char	s_handler(char **cur, char *next, int *i, t_md5 *flags)
{
	(*cur)++;
	if (**cur)
	{
		hash_handler(ft_strdup(*cur), flags);
		*cur += ft_strlen(*cur);
	}
	else if (next)
	{
		(*i)++;
		hash_handler(ft_strdup(next), flags);
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
	hash_handler(input_value, flags);
	return (1);
}

/*
** returns 1 if something has been outputed.
** returns 0 if nothing has been outputed.
*/

char	dispatcher_flags(char **cur, char *next, int *i, t_md5 *flags)
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

static char	parse_flags(char *av[], int ac, int *i, t_md5 *flags)
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

static void	file_handler(char *file_name, t_md5 *flags)
{
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("md5: %s: No such file or directory\n", file_name);
		exit(0);
	}
	else if (read(fd, NULL, 0) < 0)
	{
		ft_printf("md5: %s: Is a directory\n", file_name);
		exit(0);
	}
	hash_handler(read_data(fd), flags);
	close(fd);
}

static char	parse_files(char *av[], int ac, int *i, t_md5 *flags)
{
	char	flag_output;

	flag_output = 0;
	while (*i < ac)
	{
		file_handler(av[*i], flags);
		flag_output = 1;
		(*i)++;
	}
	return (flag_output);
}

/*
** @param flags - pointer to a structure in which I save all the flags that appears.
** @param flag_output - represents whether something was outputed or not, during parsing flags or parsing files (just because I need to loop to get input data from user and hash it).
** @param i - counter for av (arguments);
*/

void		md5(int ac, char *av[])
{
	t_md5	*flags;
	char	flag_output;
	int		i;

	flags = ft_memalloc(sizeof(t_md5 *));
	(!flags) ? ft_error("Error: something wrong with malloc") : 0;
	i = 2;
	flag_output = 0;
	flag_output |= parse_flags(av, ac, &i, flags);
	flag_output |= parse_files(av, ac, &i, flags);
	if (flag_output == 0)
		hash_handler(read_data(0), flags);
}
