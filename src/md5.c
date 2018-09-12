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
		data = ft_strjoinfree(data, line, (data) ? 3 : 2);	//	if data != NULL => we need to free data.
	}
	return (data);
}

static char	*s_handler(char **cur, char *next, int *i, t_md5 *flags)
{
	char	*tmp;

	(*cur)++;
	if (**cur)	//	if something comes after 's'.
	{
		tmp = ft_strdup(*cur);
		*cur += ft_strlen(*cur);
		return (tmp);
	}
	else if (next)
	{
		(*i)++;
		tmp = ft_strdup(next);
	}
	else
	{
		ft_error("Error invalid using of -s flag");
	}
	return (tmp);
}

static char	*p_handler(char **cur, t_md5 *flags)
{
	if (!flags->p)
	{
		flags->p = 1;
		return (read_data(0));
	}
	return (NULL);
}

char	*dispatcher_flags(char **cur, char *next, int *i, t_md5 *flags)
{
	if (**cur == 'q')
	{
		flags->q = 1;
	}
	else if (**cur == 'r')
	{
		flags->r = 1;
	}
	else if (**cur == 'p')
	{
		return (p_handler(cur, flags));
	}
	else if (**cur == 's')
	{
		return (s_handler(cur, next, i, flags));
	}
	else
	{
		ft_error("Error 0");
	}
	return (NULL);
}

char	*get_input_parse_flags(char **cur, char *next, int *i, t_md5 *flags)
{
	char	*data;

	data = NULL;
	while (**cur && !data)
	{
		data = dispatcher_flags(cur, next, i, flags);
		if (**cur)
			(*cur)++;
	}
	return (data);
}

/*
** This function parses flags in one argument.
**
** return value : if something have been outputed - 1, else - 0.
*/

static char	parse_flags_arg(char *cur, char *next, int *i, t_md5 *flags)
{
	char	*input_value;
	char	*hashed_value;
	char	flag_output;

	flag_output = 0;
	if (ft_strequ(cur, "--"))
	{
		(*i)++;
		return (IS_NOT_A_FLAG);
	}
	else if (*cur != '-' || !*(cur++))	//	if string doesn't begin with '-' or string is just a '-' => is not a flag.
		return (IS_NOT_A_FLAG);

	//	Here we already skip first character which was '-'.

	while ((input_value = get_input_parse_flags(&cur, next, i, flags)))
	{
		flag_output = 1;
		ft_printf("%s", input_value);

		// hashed_value = hash(input_value);
		// output(input_value, hashed_value, flags);
		// ft_memdel(&input_value);
		// ft_memdel(&hashed_value);
	}

	return (flag_output);
}

/*
** return value : if something have been outputed - 1, else - 0.
*/

static char	parse_flags(char *av[], int ac, int *i, t_md5 *flags)
{
	char	flag_output;
	char	tmp;

	flag_output = 0;
	while (*i < ac)
	{
		tmp = parse_flags_arg(av[*i], av[*i + 1], i, flags);	//	ATTENTION.
		if (tmp == IS_NOT_A_FLAG)	//	argument is not a flag.
			return (flag_output);
		flag_output |= tmp;
		(*i)++;
	}
	return (flag_output);
}

static void	file_handler(char *file_name, t_md5 *flags)
{
	char	*input_value;
	char	*hashed_value;
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) < 0)
		ft_error("ERROR invalid file");
	input_value = read_data(fd);
	ft_printf("%s", input_value);

	// hashed_value = hash(input_value);
	// output(input_value, hashed_value, flags);
	// ft_memdel(&input_value);
	// ft_memdel(&hashed_value);
	close(fd);
}

/*
** return value : if something have been outputed - 1, else - 0.
*/

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

void		md5(int ac, char *av[])
{
	char	*input_value;
	char	*hashed_value;
	t_md5	*flags;
	char	flag_output;
	int		i;

	flags = ft_memalloc(sizeof(t_md5 *));
	(!flags) ? ft_error("ERROR MALLOC") : 0;
	i = 2;
	flag_output = 0;
	flag_output |= parse_flags(av, ac, &i, flags);
	flag_output |= parse_files(av, ac, &i, flags);
	if (!flag_output)
	{
		input_value = read_data(0);
		ft_printf("%s", input_value);
		
		// hashed_value = hash(input_value);
		// output(input_value, hashed_value, flags);
		// ft_memdel(&input_value);
		// ft_memdel(&hashed_value);
	}
}
