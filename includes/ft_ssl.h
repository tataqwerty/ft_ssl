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

typedef struct		s_md5_sha
{
	unsigned char	q : 1;
	unsigned char	r : 1;
	unsigned char	p : 1;
	unsigned char	s : 1;
	unsigned char	file : 1;
}					t_md5_sha;



// typedef struct
// {
	
// }	t_flags;

/*
** @param name - name of command.
** @param hash - function that represents hash algorithm.
** @param parse - parsing function.
** @param output - function responsible for the output formatting.
*/

typedef struct	s_command
{
	char		*name;
	char		*(*hash)(char *);
	char		(*parse)();
	void		(*output)();
}				t_command;

void			ft_error(char *s);
void			usage(void);

char	*md5_hash(char *input);
char	md5_sha_parser(int ac, char *av[]);
void	md5_sha_output(void);

static t_command	g_commands[COUNT_COMMANDS] = {
	{"md5", md5_hash, md5_sha_parser, md5_sha_output}
	// {"sha256", sha_256}
};

#endif
