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

static void		show_commands(char *str)
{
	ft_printf("error message\n");
	exit(0);
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
		command->f(command, ac, av);
	}
	return (0);
}
