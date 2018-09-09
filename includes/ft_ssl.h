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

typedef struct		s_md5
{
	unsigned char	q : 1;
	unsigned char	p : 1;
	unsigned char	r : 1;
	unsigned char	s : 1;
}					t_md5;

typedef struct		s_sha_256
{
	unsigned char	q : 1;
	unsigned char	p : 1;
	unsigned char	r : 1;
	unsigned char	s : 1;
}					t_sha_256;

/*
** @param name - name of command.
** @param hash_f - hash function (input data, flags).
** @param parse_f - function responsible for parsing arguments (ac, av, flags).
** @param output_f - function that is responsible for output (input data, output data, flags).
** @param flags - pointer to a structure with flags, every command has different flags.
*/

typedef struct	s_command
{
	char		*name;
	void		*flags;
	char		*(*hash_f)(char *, void *);
	void		(*parse_f)(int, char **, void *);
	void		(*output_f)(char *, char *, void *);
}				t_command;

void			ft_error(char *s);

char			*md5(char *input_data, void *flags);
void			md5_parse(int ac, char *av[], void *flags);
void			md5_output(char *input_data, char *output_data, void *flags);

char			*sha256(char *input_data, void *flags);
void			sha256_parse(int ac, char *av[], void *flags);
void			sha256_output(char *input_data, char *output_data, void *flags);

static t_command	g_commands[COUNT_COMMANDS] = {
	{"md5", NULL, md5, md5_parse, md5_output},
	{"sha256", NULL, sha256, sha256_parse, sha256_output}
};

#endif
