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

# define COUNT_COMMANDS	1

# define IS_NOT_A_FLAG -1

typedef struct		s_md5_sha_data
{
	struct 			s_flags
	{
		unsigned char	q : 1;
		unsigned char	p : 1;
		unsigned char	r : 1;
		unsigned char	s : 1;
		unsigned char	file : 1;
		unsigned char	p_used : 1;	//	for output.
	}				flags;
	char			*name;
	char			*input;
	char			*hashed;
	size_t			size;
}					t_md5_sha_data;

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
	char		(*parse)(char **, int *, int *, struct s_command *);
	void		(*output)(struct s_command *);
	void		*(*init_data)(void);
	void		*data;
}				t_command;

void			ft_error(char *s);
char			*read_data(int fd, size_t *size);

// MD5 SHA
char	*md5_hash(char *input);
char	md5_sha_parser(char *av[], int *i, int *j, t_command *command);
void	md5_sha_output(t_command *command);
void	*md5_sha_init_data(void);

static t_command	g_commands[COUNT_COMMANDS] = {
	{"md5", md5_hash, md5_sha_parser, md5_sha_output, md5_sha_init_data}
};

#endif
