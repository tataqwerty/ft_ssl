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
char			*read_data(int fd);


void			hash_handler(char *input_value, t_md5 *flags, char *(*hash)(char *), void (*output)(char *, char *, void *));

/* MD5 */
char			md5_parse_flags(char *av[], int ac, int *i, t_md5 *flags);
char			md5_parse_files(char *av[], int ac, int *i, t_md5 *flags);
void			md5_output(char *input_value, char *hashed_value, void *flags);
char			*md5_hash(char *input);



void			md5(int ac, char *av[]);
void			sha256(int ac, char *av[]);

static t_command	g_commands[COUNT_COMMANDS] = {
	{"md5", md5},
	{"sha256", sha256}
};

#endif
