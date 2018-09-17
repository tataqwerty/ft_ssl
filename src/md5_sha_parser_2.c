#include <ft_ssl.h>

// I don't know where it should be.

void	*md5_sha_init_data(void)
{
	t_md5_sha_data	*data;

	data = ft_memalloc(sizeof(t_md5_sha_data));
	(!data) ? ft_error("Error with malloc") : 0;
	ft_bzero(data, sizeof(t_md5_sha_data));
	return (data);
}

void	md5_sha_usage(char *name)
{
	ft_printf("usage: %s [-pqrtx] [-s string] [files ...]\n", name);
	exit(0);
}

void	p_handler(char *av[], int *i, int *j, t_md5_sha_data *data)
{
	static char p_used;

	data->flags.p = 1;
	if (!p_used)
	{
		p_used = 1;
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
	data->flags.s = 1;
	(*j)++;
	if (av[*i][*j])	// -sasdad
	{
		data->name = &av[*i][*j];
		data->input = ft_strdup(&av[*i][*j]);
		data->size = ft_strlen(data->input);
		(*i)++;
		*j = 0;
	}
	else if (av[*i + 1])	// -s asd
	{
		data->name = av[*i + 1];
		data->input = ft_strdup(av[*i + 1]);
		data->size = ft_strlen(data->input);
		*i += 2;
		*j = 0;
	}
	else	// -s
	{
		ft_printf("%s: option requires an argument -- s\n", command->name);
		md5_sha_usage(command->name);
	}
}

void	md5_sha_flag_router(char *av[], int *i, int *j, t_command *command)
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
		p_handler(av, i, j, data);
	else if (av[*i][*j] == 's')
		s_handler(av, i, j, command);
	else
	{
		ft_printf("%s: illegal option -- %c\n", command->name, av[*i][*j]);
		md5_sha_usage(command->name);
	}
}
