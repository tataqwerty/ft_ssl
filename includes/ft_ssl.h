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

/*
** @param name - name of a file, or a string (-s 'string'), just for output.
** @param size - size of input.
*/

typedef struct		s_md5_sha_data
{
	struct 			s_flags
	{
		unsigned char	q : 1;
		unsigned char	p : 1;
		unsigned char	r : 1;
		unsigned char	s : 1;
		unsigned char	file : 1;
	}				flags;
	char			*name;
	char			*input;
	char			*hashed;
	size_t			size;
}					t_md5_sha_data;

/*
** @param init_data - function that initializes data.
** (each command have different init function,
** because each command needs different data types).
*/

typedef struct	s_command
{
	char		*name;
	char		*(*hash)(char *);
	char		(*parse)(char **, int *, int *, struct s_command *);
	void		(*output)(struct s_command *);
	void		*(*init_data)(void);
	void		*data;
}				t_command;

/*
** staff functions (functions that I use everywhere).
*/
void			ft_error(char *s);
char			*read_data(int fd, size_t *size);

/*
** hash functions.
*/
char	*md5_hash(char *input);
char	*sha256_hash(char *input);

// MD5 SHA
void	md5_sha_flag_router(char *av[], int *i, int *j, t_command *command);
char	md5_sha_parser(char *av[], int *i, int *j, t_command *command);
void	md5_sha_output(t_command *command);
void	*md5_sha_init_data(void);

static t_command	g_commands[COUNT_COMMANDS] = {
	{"md5", md5_hash, md5_sha_parser, md5_sha_output, md5_sha_init_data},
	{"sha256", sha256_hash, md5_sha_parser, md5_sha_output, md5_sha_init_data}
};

#endif
