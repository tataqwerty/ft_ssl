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
# define LEFT_ROTATE(x, c) (x << c) | (x >> (32 - c));


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
	unsigned char	*hashed;
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
	unsigned char	*(*hash)(char *, size_t);
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
unsigned char	*md5_hash(char *input, size_t size);
// char	*sha256_hash(char *input, size_t size);

// MD5 SHA
void	md5_block_handler(unsigned char *hashed, unsigned int buffers[]);
void	md5_sha_flag_router(char *av[], int *i, int *j, t_command *command);
char	md5_sha_parser(char *av[], int *i, int *j, t_command *command);
void	md5_sha_output(t_command *command);
void	*md5_sha_init_data(void);

static t_command	g_commands[COUNT_COMMANDS] = {
	{"md5", md5_hash, md5_sha_parser, md5_sha_output, md5_sha_init_data}
	// {"sha256", sha256_hash, md5_sha_parser, md5_sha_output, md5_sha_init_data}
};

static size_t	g_table_t[64] = {
	3614090360, 3905402710, 606105819, 3250441966, 4118548399, 1200080426, 2821735955, 4249261313,
	1770035416, 2336552879, 4294925233, 2304563134, 1804603682, 4254626195, 2792965006, 1236535329,
	4129170786, 3225465664, 643717713, 3921069994, 3593408605, 38016083, 3634488961, 3889429448,
	568446438, 3275163606, 4107603335, 1163531501, 2850285829, 4243563512, 1735328473, 2368359562,
	4294588738, 2272392833, 1839030562, 4259657740, 2763975236, 1272893353, 4139469664, 3200236656,
	681279174, 3936430074, 3572445317, 76029189, 3654602809, 3873151461, 530742520, 3299628645,
	4096336452, 1126891415, 2878612391, 4237533241, 1700485571, 2399980690, 4293915773, 2240044497,
	1873313359, 4264355552, 2734768916, 1309151649, 4149444226, 3174756917, 718787259, 3951481745
};

static size_t	g_table_s[64] = {
	7, 12, 17, 22, 7, 12, 17, 22,
	7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20,
	5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23,
	4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21,
	6, 10, 15, 21, 6, 10, 15, 21
};

#endif
