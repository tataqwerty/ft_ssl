#include <ft_ssl.h>

static void	add_one_byte(unsigned char **input, size_t *size, unsigned char byte)
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

static void	align_input(unsigned char **input, size_t *size)
{
	add_one_byte(input, size, 128);	//	10000000
	while ((*size % 64) != 56)
		add_one_byte(input, size, 0);
}

static void	add_input_size(unsigned char **input, size_t *size, size_t input_size)
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

static void	create_hash(unsigned char **hash, unsigned int buffers[])
{
	unsigned char	*base;
	unsigned char	*tmp;
	unsigned char	i;
	unsigned char	j;
	unsigned char	k;

	base = (unsigned char *)"0123456789abcdef";
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

unsigned char	*md5_hash(char *input, size_t size)
{
	unsigned char	*hashed;
	unsigned int	buffers[4];
	size_t			input_size;
	size_t			i;			//	counter for 512 blocks
	size_t			blocks_len;	//	quantity of 512 blocks

	input_size = size * 8;
	(!(hashed = ft_memalloc(size))) ? ft_error("Error with malloc") : 0;
	ft_memcpy(hashed, input, size);
	align_input((unsigned char **)&hashed, &size);
	add_input_size((unsigned char **)&hashed, &size, input_size);
	buffers[0] = 0x67452301;
	buffers[1] = 0xefcdab89;
	buffers[2] = 0x98badcfe;
	buffers[3] = 0x10325476;
	i = 0;
	blocks_len = size / 64;
	while (i < blocks_len)
		md5_block_handler(hashed + (i++ * 64), buffers);
	ft_memdel((void **)&hashed);
	create_hash(&hashed, buffers);
	return (hashed);
}
