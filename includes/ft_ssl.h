/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 12:12:31 by tkiselev          #+#    #+#             */
/*   Updated: 2018/09/23 16:43:13 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <libft.h>

# define COUNT_COMMANDS		2
# define IS_NOT_A_FLAG		-1
# define LEFT_ROTATE(x, c)	((x << c) | (x >> (32 - c)))
# define RIGHT_ROTATE(x, c)	((x >> c) | (x << (32 - c)))
# define RIGHT_SHIFT(x, c)	(x >> c)

# define STANDART_CMD		0
# define MD_CMD				1
# define CIPHER_CMD			2

/*
** @param name - name of a file, or a string (-s 'string'), just for output.
** @param size - size of input.
*/

typedef struct			s_md5_sha_data
{
	struct				s_flags
	{
		unsigned char	q : 1;
		unsigned char	p : 1;
		unsigned char	r : 1;
		unsigned char	s : 1;
		unsigned char	file : 1;
	}					flags;
	char				*name;
	char				*input;
	unsigned char		*hashed;
	size_t				size;
}						t_md5_sha_data;

/*
** @param init_data - function that initializes data.
** (each command have different init function,
** because each command needs different data types).
*/

typedef struct			s_command
{
	char				*name;
	unsigned char		*(*hash)(char *, size_t);
	char				(*parse)(char **, int *, int *, struct s_command *);
	void				(*output)(struct s_command *);
	void				*(*init_data)(void);
	void				*data;
	char				type;
}						t_command;

/*
** staff functions (functions that I use everywhere).
*/
void					ft_error(char *s);
char					*read_data(int fd, size_t *size);
size_t					reverse_bytes(size_t n, unsigned char bytes);

/*
** hash functions.
*/
unsigned char			*md5_hash(char *input, size_t size);
unsigned char			*sha256_hash(char *input, size_t size);

/*
** MD5 SHA
*/
void					init_buffers(unsigned int buffers[],
						unsigned int array[]);
unsigned char			*md5_sha_get_padded_input(char *input, size_t *size);
void					copy_16_words(unsigned int w[], unsigned char *hashed);
void					md5_sha_create_hash(unsigned char **hash,
						unsigned int buffers[], int hash_size, int buffers_n);
void					md5_sha_flag_router(char *av[], int *i, int *j,
						t_command *command);
char					md5_sha_parser(char *av[], int *i, int *j,
						t_command *command);
void					md5_sha_output(t_command *command);
void					*md5_sha_init_data(void);

static t_command		g_commands[COUNT_COMMANDS] = {
	{
		"md5",
		md5_hash,
		md5_sha_parser,
		md5_sha_output,
		md5_sha_init_data,
		NULL,
		MD_CMD
	},
	{
		"sha256",
		sha256_hash,
		md5_sha_parser,
		md5_sha_output,
		md5_sha_init_data,
		NULL,
		MD_CMD
	}
};

static unsigned int		g_table_md5_sha_t[64] = {
	3614090360, 3905402710, 606105819, 3250441966,
	4118548399, 1200080426, 2821735955, 4249261313,
	1770035416, 2336552879, 4294925233, 2304563134,
	1804603682, 4254626195, 2792965006, 1236535329,
	4129170786, 3225465664, 643717713, 3921069994,
	3593408605, 38016083, 3634488961, 3889429448,
	568446438, 3275163606, 4107603335, 1163531501,
	2850285829, 4243563512, 1735328473, 2368359562,
	4294588738, 2272392833, 1839030562, 4259657740,
	2763975236, 1272893353, 4139469664, 3200236656,
	681279174, 3936430074, 3572445317, 76029189,
	3654602809, 3873151461, 530742520, 3299628645,
	4096336452, 1126891415, 2878612391, 4237533241,
	1700485571, 2399980690, 4293915773, 2240044497,
	1873313359, 4264355552, 2734768916, 1309151649,
	4149444226, 3174756917, 718787259, 3951481745
};

static unsigned int		g_table_md5_sha_s[64] = {
	7, 12, 17, 22, 7, 12, 17, 22,
	7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20,
	5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23,
	4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21,
	6, 10, 15, 21, 6, 10, 15, 21
};

static unsigned int		g_table_sha256_k[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

#endif
