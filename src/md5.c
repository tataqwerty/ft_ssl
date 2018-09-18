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

int		func_f(int x, int y, int z)
{
	int res;

	return (res);
}

int		func_g(int x, int y, int z)
{
	int res;

	return (res);
}

int		func_h(int x, int y, int z)
{
	int res;

	return (res);
}

int		func_i(int x, int y, int z)
{
	int res;

	return (res);
}

static void	init_buffers(t_md5_sha_buffers	*buffers)
{
	buffers->a = 1732584193;
	buffers->b = 4023233417;
	buffers->c = 2562383102;
	buffers->d = 271733878;
}

char	*md5_hash(char *input, size_t size)
{
	static t_md5_sha_buffers	buffers;
	char	*hashed;
	size_t	input_size;

	input_size = size * 8;				//	bits
	hashed = ft_strdup(input);			//	doesn't work with binaries.
	align_input(&hashed, &size);
	add_input_size(&hashed, &size, input_size);
	init_buffers(&buffers);

	return (hashed);
}
