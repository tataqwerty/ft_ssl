#include <ft_ssl.h>

void	add_one_byte(unsigned char **input, size_t *size, unsigned char byte)
{
	unsigned char	*new;
	size_t			i;

	if (!(new = (unsigned char *)ft_strnew(*size + 1)))
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

void	align_input(unsigned char **input, size_t *size)
{
	add_one_byte(input, size, 128);	//	10000000
	while ((*size % 64) != 56)
		add_one_byte(input, size, 0);
}

void	add_input_size(unsigned char **input, size_t *size, size_t input_size)
{
	unsigned char	*new;
	unsigned char	*input_size_ptr;
	size_t			i;
	unsigned char	j;

	if (!(new = (unsigned char *)ft_strnew(*size + 8)))
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
		new[i + j] = input_size_ptr[j];
		j++;
	}
	*size += 8;
	free(*input);
	*input = new;
}

void	copy_4_bytes(unsigned char *dest, unsigned char *src)
{
	dest[0] = src[0];
	dest[1] = src[1];
	dest[2] = src[2];
	dest[3] = src[3];
}

void	copy_16_words(unsigned int M[], unsigned char *hashed)
{
	unsigned char	i;

	i = 0;
	while (i < 16)
	{
		copy_4_bytes((unsigned char *)&M[i], hashed);
		i++;
		hashed += 4;
	}
}

void	operation_switcher(unsigned int abcd[], unsigned int *F, unsigned int *g, unsigned int i)
{
	if (i <= 15)
	{
		*F = (abcd[1] & abcd[2]) | (~abcd[1] & abcd[3]);
		*g = i;
	}
	else if (i >= 16 && i <= 31)
	{
		*F = (abcd[3] & abcd[1]) | (~abcd[3] & abcd[2]);
		*g = (5 * i + 1) % 16;
	}
	else if (i >= 32 && i <= 47)
	{
		*F = abcd[1] ^ abcd[2] ^ abcd[3];
		*g = (3 * i + 5) % 16;
	}
	else if (i >= 48 && i <= 63)
	{
		*F = abcd[2] ^ (abcd[1] | ~abcd[3]);
		*g = (7 * i) % 16;
	}
}

unsigned int leftrotate(unsigned int x, unsigned int c)
{
	return ((x << c) | (x >> (32 - c)));
}

void	block_handler(unsigned char *hashed, unsigned int buffers[])
{
	unsigned int	abcd[4];
	unsigned int	M[16];
	unsigned int	F;
	unsigned int	g;
	int				i;

	copy_16_words(M, hashed);
	abcd[0] = buffers[0];
	abcd[1] = buffers[1];
	abcd[2] = buffers[2];
	abcd[3] = buffers[3];
	i = -1;
	while (++i < 64)
	{
		operation_switcher(abcd, &F, &g, i);
		F = F + abcd[0] + g_table_t[i] + M[g];
		abcd[0] = abcd[3];
		abcd[3] = abcd[2];
		abcd[2] = abcd[1];
		abcd[1] += leftrotate(F, g_table_s[i]);
	}
	buffers[0] += abcd[0];
	buffers[1] += abcd[1];
	buffers[2] += abcd[2];
	buffers[3] += abcd[3];
}

void	create_hash(unsigned char **hash, unsigned int buffers[])
{
	unsigned char	*base;
	unsigned char	*tmp;
	unsigned char	i;
	unsigned char	j;
	unsigned char	k;

	base = "0123456789abcdef";
	(!(*hash = ft_memalloc(33))) ? ft_error("Error with malloc") : 0;
	i = 0;
	j = 0;
	while (i < 4)
	{
		tmp = (unsigned char *)&buffers[i];
		k = 0;
		while (k < 4)
		{
			(*hash)[j++] = base[tmp[k] / 16];
			(*hash)[j++] = base[tmp[k] % 16];
			k++;
		}
		i++;
	}
}

unsigned char		*md5_hash(char *input, size_t size)
{
	unsigned char	*hashed;
	unsigned int	buffers[4];
	size_t			input_size;
	size_t			i;			//	counter for 512 blocks
	size_t			blocks_len;	//	quantity of 512 blocks

	input_size = size * 8;
	hashed = (unsigned char *)ft_strdup(input);
	align_input(&hashed, &size);
	add_input_size(&hashed, &size, input_size);
	buffers[0] = 0x67452301;
	buffers[1] = 0xefcdab89;
	buffers[2] = 0x98badcfe;
	buffers[3] = 0x10325476;
	i = 0;
	blocks_len = size / 64;
	while (i < blocks_len)
		block_handler(hashed + (i++ * 64), buffers);
	ft_strdel((char **)&hashed);
	create_hash(&hashed, buffers);
	return (hashed);
}
