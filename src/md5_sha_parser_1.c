/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_sha_parser_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 16:45:40 by tkiselev          #+#    #+#             */
/*   Updated: 2018/09/23 16:45:41 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

/*
** @return 0 - argument have been parsed, but input have not been received.
** @return 1 - input have been received.
** @return -1 (IS_NOT_A_FLAG) - argument is not a flag.
*/

static char	parse_flags_in_arg(char *av[], int *i, int *j, t_command *command)
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
		md5_sha_flag_router(av, i, j, command);
		if (((t_md5_sha_data *)command->data)->input)
			return (1);
	}
	return (0);
}

/*
** @return 1 - input was received.
** @return 0 - input was not received.
**
** @param result - represents result of parsing of a single argument.
*/

static char	parse_flags(char *av[], int *i, int *j, t_command *command)
{
	char	result;

	while (av[*i])
	{
		result = parse_flags_in_arg(av, i, j, command);
		if (result == IS_NOT_A_FLAG)
			break ;
		if (result)
			return (1);
		(*i)++;
		*j = 0;
	}
	return (0);
}

static void	parse_file(char *file_name, t_command *command)
{
	t_md5_sha_data	*data;
	int				fd;

	data = (t_md5_sha_data *)command->data;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("%s: %s: No such file or directory\n",
		command->name, file_name);
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
		data->flags.file = 1;
		close(fd);
	}
}

static char	parse_files(char *av[], int *i, t_command *command)
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
** @return 1 - input was received.
** @return 0 - input was not received.
*/

char		md5_sha_parser(char *av[], int *i, int *j, t_command *command)
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
	if (parse_files(av, i, command))
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
