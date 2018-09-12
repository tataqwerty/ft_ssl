#include <ft_ssl.h>

char	*hash()
{
	return (NULL);
}

char	*read_data(int fd)
{
	char	*line;
	char	*data;

	line = NULL;
	data = NULL;
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

	tmp = NULL;
	(*cur)++;	//	SKIP 's'
	if (**cur)
	{
		tmp = ft_strdup(*cur);
		*cur += ft_strlen(*cur);	//	here we are at the end of cur.
	}
	else if (next)
	{
		tmp = ft_strdup(next);
		(*i)++;
	}
	else
		ft_error("ERROR invalid using of flag s");
	return (tmp);
}

char	*get_input_and_parse_flags(char **cur, char *next, int *i, t_md5 *flags)
{
	while (**cur)
	{
		if (**cur == 'q')
			flags->q = 1;
		else if (**cur == 'r')
			flags->r = 1;
		else if (**cur == 'p')
		{
			(*cur)++;
			return (read_data(0));
		}
		else if (**cur == 's')
			return (s_handler(cur, next, i, flags));
		else
			ft_error("Error undefined flag");
		(*cur)++;
	}
	return (NULL);
}

char	parse_flags(char *cur, char *next, int *i, t_md5 *flags)
{
	char	*input_value;
	char	*hashed_value;

	input_value = NULL;
	hashed_value = NULL;
	if (ft_strequ(cur, "--"))
	{
		(*i)++;
		return (0);
	}
	if (*cur != '-')
		return (0);
	cur++;	// SKIP '-'
	if (!*cur)
		ft_error("Error not a valid flag");
	while ((input_value = get_input_and_parse_flags(&cur, next, i, flags)))
	{
		ft_printf("input_value = %s\n", input_value);
		// hashed_value = hash(input_value);
		// output(input_value, hashed_value, flags);
		// ft_memdel(&input_value);
		// ft_memdel(&hashed_value);
	}
	return (1);
}

char	md5_flags(int ac, char *av[], int *i, t_md5 *flags)
{
	if ((*i + 1) < ac)	//	We have current and next element.
	{
		return (parse_flags(av[*i], av[*i + 1], i, flags));
	}
	else
	{
		return (parse_flags(av[*i], NULL, i, flags));
	}
}

void	md5_files(char *cur, t_md5 *flags)
{
	char	*input_value;
	char	*hashed_value;
	int fd;

	fd = open(cur, O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) < 0)
		ft_error("ERROR INVALID FILE");
	input_value = read_data(fd);
	ft_printf("input_value = %s\n", input_value);
	// hashed_value = hash(input_value);
	// output(input_value, hashed_value, flags);
	// ft_memdel(&input_value);
	// ft_memdel(&hashed_value);
	close(fd);
}

void	md5(int ac, char *av[])
{
	t_md5	*flags;
	int		i;

	flags = ft_memalloc(sizeof(t_md5 *));
	i = 2;
	while (i < ac)
	{
		if (!md5_flags(ac, av, &i, flags))
			break ;
		i++;
	}
	while (i < ac)
	{
		md5_files(av[i], flags);
		i++;
	}
}
