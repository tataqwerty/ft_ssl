/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 11:40:59 by tkiselev          #+#    #+#             */
/*   Updated: 2018/09/09 12:13:29 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

static t_command	*get_command(char *str)
{
	int i;

	i = 0;
	while (i < COUNT_COMMANDS)
	{
		if (ft_strequ(g_commands[i].name, str))
			return (&g_commands[i]);
		i++;
	}
	return (NULL);
}

static void		output_commands(char type)
{
	int i;

	i = 0;
	while (i < COUNT_COMMANDS)
	{
		if (g_commands[i].type == type)
			ft_printf("%s\n", g_commands[i].name);
		i++;
	}
}

static void		show_commands(char *str)
{
	ft_printf("ft_ssl:Error: '%s' is an invalid command.\n", str);
	ft_printf("\nStandart commands:\n");
	output_commands(STANDART_CMD);
	ft_printf("\nMessage Digest commands:\n");
	output_commands(MD_CMD);
	ft_printf("\nCipher commands:\n");
	output_commands(CIPHER_CMD);
	exit(0);
}

/*
** It is a function that parses, hashes, and outputs, for each kind of command.
** MD5 and SHA have different hash functions, but have the same parser and output functions.
**
** @param i - represents counter for arguments (av).
** @param j - represents counter for a single argument.
*/

static void	ft_ssl_template(t_command *command, int ac, char *av[])
{
	int		i;
	int		j;

	i = 2;
	j = 0;
	command->data = command->init_data();
	while (command->parse(av, &i, &j, command))	//	RETURNS 1 OR 0
	{
		/* I have to pass there command, because I can not pass there data
		** (command->data->hashed = command->hash(command->data->input)), 
		** cause command->data is of type void,
		** so I need to cast it to a different type.
		**
		** So, the solution is to call hash function in output function.
		*/
		command->output(command);
	}
}

int				main(int ac, char *av[])
{
	t_command	*command;

	if (ac < 2)
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	else
	{
		command = get_command(av[1]);
		(!command) ? show_commands(av[1]) : 0;
		ft_ssl_template(command, ac, av);
	}
	return (0);
}
