/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 12:12:31 by tkiselev          #+#    #+#             */
/*   Updated: 2018/09/09 16:23:09 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <libft.h>

# define COUNT_COMMANDS	2



# define IS_NOT_A_FLAG -1


typedef struct		s_md5
{
	unsigned char	q : 1;
	unsigned char	r : 1;
	unsigned char	p : 1;
}					t_md5;

typedef struct		s_sha_256
{
	unsigned char	q : 1;
	unsigned char	r : 1;
	unsigned char	p : 1;
}					t_sha_256;

/*
** @param name - name of command.
** @param f - function that represents certain algorithm that needs to be executed.
*/

typedef struct	s_command
{
	char		*name;
	void		(*f)(int, char **);
}				t_command;

void			ft_error(char *s);
void			usage(void);


void			md5(int ac, char *av[]);
void			sha256(int ac, char *av[]);

static t_command	g_commands[COUNT_COMMANDS] = {
	{"md5", md5},
	{"sha256", sha256}
};

#endif
