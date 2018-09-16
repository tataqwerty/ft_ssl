#include <ft_ssl.h>

void	md5_sha_usage(char *name)
{
	ft_printf("usage: %s [-pqrtx] [-s string] [files ...]\n", name);
	exit(0);
}

void	*md5_sha_init_data(void)
{
	t_md5_sha_data	*data;

	data = ft_memalloc(sizeof(t_md5_sha_data));
	(!data) ? ft_error("Error with malloc") : 0;
	ft_bzero(data, sizeof(t_md5_sha_data));
	return (data);
}

// HASH

char	*md5_hash(char *input)
{
	return (ft_strdup(input));
}






//	OUTPUT

void	md5_sha_output(t_command *command)
{
	t_md5_sha_data *data;

	data = (t_md5_sha_data *)command->data;
	data->hashed = command->hash(data->input);
	ft_printf("input_name ===> %s\n", data->name);
	ft_printf("input_value ===> %s\n", data->input);
	ft_printf("input_hashed ===> %s\n", data->hashed);

	// print_memory(data->input, data->size);

	data->name = NULL;
	ft_strdel(&data->input);
	ft_strdel(&data->hashed);
	data->size = 0;
}






//	PARSER


void	p_handler(char *av[], int *i, int *j, t_md5_sha_data *data)
{
	if (!data->flags.p)
	{
		data->flags.p = 1;
		data->input = read_data(0, &data->size);
	}
	else
	{
		data->input = ft_strdup("");
	}
	(*j)++;
}

void	s_handler(char *av[], int *i, int *j, t_command *command)
{
	t_md5_sha_data	*data;

	data = (t_md5_sha_data *)command->data;
	(*j)++;
	if (av[*i][*j])
	{
		data->name = &av[*i][*j];	// i can do it without strdup
		data->input = ft_strdup(&av[*i][*j]);	//	This shit will be hashed
		data->size = ft_strlen(data->input);
		(*i)++;
		*j = 0;
	}
	else if (av[*i + 1])
	{
		data->name = av[*i + 1];		// i can do it without strdup
		data->input = ft_strdup(av[*i + 1]);	//	This shit will be hashed
		data->size = ft_strlen(data->input);
		*i += 2;
		*j = 0;
	}
	else
	{
		ft_printf("%s: option requires an argument -- s\n", command->name);
		md5_sha_usage(command->name);
	}
}

void	flag_router(char *av[], int *i, int *j, t_command *command)
{
	t_md5_sha_data *data;

	data = (t_md5_sha_data *)command->data;
	if (av[*i][*j] == 'q')
	{
		data->flags.q = 1;
		(*j)++;
	}
	else if (av[*i][*j] == 'r')
	{
		data->flags.r = 1;
		(*j)++;
	}
	else if (av[*i][*j] == 'p')
	{
		p_handler(av, i, j, data);
	}
	else if (av[*i][*j] == 's')
	{
		s_handler(av, i, j, command);
	}
	else
	{
		ft_printf("%s: illegal option -- %c\n", command->name, av[*i][*j]);
		md5_sha_usage(command->name);
	}
}

/*
** returns:
** 1 - if input have been received,
** 0 - if just flags have been parsed,
** IS_NOT_A_FLAG (-1) - if argument is not a flag.
*/

char	parse_flags_in_arg(char *av[], int *i, int *j, t_command *command)
{
	if (ft_strequ(av[*i], "--"))
	{
		(*i)++;
		return (IS_NOT_A_FLAG);
	}
	else if (av[*i][0] != '-' || ft_strlen(av[*i]) == 1)
		return (IS_NOT_A_FLAG);

	if (av[*i][*j] == '-' && *j == 0)
		(*j)++;

	while (av[*i][*j])
	{
		flag_router(av, i, j, command);
		if (((t_md5_sha_data *)command->data)->input)
			return (1);
	}
	return (0);	//	argument have been parsed, but input have not been received.
}


/*
** returns 1 if input was received, 0 if not.
**
** @param result - represents result of parsing of single argument.
*/

char	parse_flags(char *av[], int *i, int *j, t_command *command)
{
	char	result;

	while (av[*i])
	{
		result = parse_flags_in_arg(av, i, j, command);

		if (result == IS_NOT_A_FLAG)
		{
			break ;	// end of flags parsing.
		}

		if (result)	// input have been received.
		{
			return (1);
		}
		(*i)++;
		*j = 0;	//	we will parse new argument.
	}
	return (0);
}

void	parse_file(char *file_name, t_command *command)
{
	t_md5_sha_data *data;
	int fd;

	data = (t_md5_sha_data *)command->data;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("%s: %s: No such file or directory\n", command->name, file_name);
		exit(0);
	}
	else if (read(fd, NULL, 0) < 0)
	{
		close(fd);
		ft_printf("%s: %s: Is a directory\n", command->name, file_name);
		exit(0);
	}
	else
	{
		data->name = file_name;
		data->input = read_data(fd, &data->size);
		close(fd);
	}
}

//	returns 1 if input was received, 0 if not.

char	parse_files(char *av[], int *i, int *j, t_command *command)
{
	if (av[*i])
	{
		parse_file(av[*i], command);
		(*i)++;
		return (1);
	}
	return (0);
}

/*
** If something was parsed (have input data to hash and output), returns 1, else 0.
*/

char	md5_sha_parser(char *av[], int *i, int *j, t_command *command)
{
	static char	flags_parsed;
	static char	flag_output;

	if (!flags_parsed)
	{
		if (parse_flags(av, i, j, command))
		{
			flag_output = 1;
			return (1);
		}
		flags_parsed = 1;
	}
	if (parse_files(av, i, j, command))
	{
		flag_output = 1;
		return (1);
	}
	if (!flag_output)
	{
		flag_output = 1;
		((t_md5_sha_data *)command->data)->input =
		read_data(0, &((t_md5_sha_data *)command->data)->size);
		return (1);
	}
	return (0);
}
