#include <ft_ssl.h>

// #define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
// #define BYTE_TO_BINARY(byte)  \
//   (byte & 0x80 ? '1' : '0'), \
//   (byte & 0x40 ? '1' : '0'), \
//   (byte & 0x20 ? '1' : '0'), \
//   (byte & 0x10 ? '1' : '0'), \
//   (byte & 0x08 ? '1' : '0'), \
//   (byte & 0x04 ? '1' : '0'), \
//   (byte & 0x02 ? '1' : '0'), \
//   (byte & 0x01 ? '1' : '0')

// void	print_binary(char *hashed, size_t size)
// {
// 	size_t i = 0;

// 	while (i < size)
// 	{
// 		printf(BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(hashed[i]));
// 		i++;
// 	}
// }

void	add_one_byte(char **input, size_t *size, unsigned char byte)
{
	char	*new;
	size_t	i;

	if (!(new = ft_strnew(*size + 1)))
		ft_error("Error with malloc");
	i = 0;
	while (i < *size)
	{
		new[i] = (*input)[i];
		i++;
	}
	new[i] |= byte;
	free(*input);
	*input = new;
	(*size)++;
}

void	align_input(char **input, size_t *size)
{
	add_one_byte(input, size, 128);
	while ((*size % 64) != 56)
		add_one_byte(input, size, 0);
}

void	add_input_size(char **input, size_t *size, size_t input_size)
{
	char			*new;
	unsigned char	*input_size_ptr;
	size_t			i;
	unsigned char	j;

	if (!(new = ft_strnew(*size + 8)))
		ft_error("Error with malloc");
	i = 0;
	while (i < *size)
	{
		new[i] = (*input)[i];
		i++;
	}
	input_size_ptr = (unsigned char *)&input_size;
	j = 0;
	while (j < 8)
	{
		new[i + j] = input_size_ptr[7 - j];
		j++;
	}
	*size += 8;
	free(*input);
	*input = new;
}

// static void	init_buffers(t_md5_sha_buffers	*buffers)
// {
// 	buffers->a = 0x67452301;
// 	buffers->b = 0xefcdab89;
// 	buffers->c = 0x98badcfe;
// 	buffers->d = 0x10325476;
// }

// void	append_buffer(char *hashed, unsigned char *buffer)
// {
// 	hashed[0] = buffer[0];
// 	hashed[1] = buffer[1];
// 	hashed[2] = buffer[2];
// 	hashed[3] = buffer[3];
// }

void	copy_4_bytes(unsigned char *dest, unsigned char *src)
{
	dest[0] = src[0];
	dest[1] = src[1];
	dest[2] = src[2];
	dest[3] = src[3];
}

void	copy_16_words(unsigned int M[], char *hashed)
{
	unsigned char	i;

	i = 0;
	while (i < 16)
	{
		copy_4_bytes(&M[i], hashed);
		i++;
		hashed += 4;
	}
}

void	operation_switcher(t_md5_sha_buffers &buffers, unsigned int *F, unsigned int *g, unsigned char i)
{
	if (i >= 0 && i <= 15)
	{
		// *F = (B and C) or ((not B) and D);
		*F = (buffers->b & buffers->c) || (!buffers->c & buffers->d);
		*g = i;
	}
	else if (i >= 16 && i <= 31)
	{
		// *F = (D and B) or ((not D) and C);
		*g = (5×i + 1) mod 16;
	}
	else if (i >= 32 && i <= 47)
	{
		*F = B xor C xor D;
		*g = (3×i + 5) mod 16;
	}
	else if (i >= 48 && i <= 63)
	{
		*F = C xor (B or (not D));
		*g = (7×i) mod 16;
	}
}

void	block_handler(char *hashed, t_md5_sha_buffers *buffers)
{
	t_md5_sha_buffers	block_buffers;
	unsigned int		M[16];
	unsigned int		F;
	unsigned int		g;
	unsigned char		i;

	i = 0;
	copy_16_words(M, hashed);
	while (i < 64)
	{
		block_buffers.a = buffers->a;
		block_buffers.b = buffers->b;
		block_buffers.c = buffers->c;
		block_buffers.d = buffers->d;

		operation_switcher(&block_buffers, &F, &g, i);

		F = ...;
		block_buffers.a = block_buffers.d;
		block_buffers.d = block_buffers.c;
		block_buffers.c = block_buffers.b;
		block_buffers.b += leftrotate();
		i++;
	}
	buffers->a += block_buffers.a;
	buffers->b += block_buffers.b;
	buffers->c += block_buffers.c;
	buffers->d += block_buffers.d;
}

char	*md5_hash(char *input, size_t size)
{
	static t_md5_sha_buffers	buffers;
	char						*hashed;
	size_t						input_size;
	size_t						i;
	size_t						len;

	input_size = size * 8;				//	bits
	hashed = ft_strdup(input);			//	doesn't work with binaries.
	align_input(&hashed, &size);
	add_input_size(&hashed, &size, input_size);
	buffers.a = 0x67452301;
	buffers.b = 0xefcdab89;
	buffers.c = 0x98badcfe;
	buffers.d = 0x10325476;
	i = 0;
	len = size / 64;
	while (i < len)
		block_handler(hashed + (i++ * 64), &buffers);
	free(hashed);
	(!(hashed = ft_memalloc(16))) ? ft_error("Error with malloc") : 0;
	// append_buffer(hashed, &buffers.a);
	// append_buffer(hashed + 4, &buffers.b);
	// append_buffer(hashed + 8, &buffers.c);
	// append_buffer(hashed + 12, &buffers.d);
	copy_4_bytes(hashed, &buffers.a);
	copy_4_bytes(hashed + 4, &buffers.b);
	copy_4_bytes(hashed + 8, &buffers.c);
	copy_4_bytes(hashed + 12, &buffers.d);
	return (hashed);
}
