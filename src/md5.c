#include <ft_ssl.h>

static size_t	get_new_size(size_t size)
{
	size++;						//	add 1
	while ((size % 64) != 56)	//	size % 512 ==> 448
		size++;
	size += 8;
	return (size);
}

static void				add_input_size(unsigned char *input, size_t added_size)
{
	unsigned char	*tmp;
	unsigned char	i;

	tmp = (unsigned char *)&added_size;
	i = 0;
	while (i < 8)
	{
		input[i] = tmp[i];
		i++;
	}
}

/*
** Add padding bits (1 + 000...)
** Add length (last 8 bytes)
*/

static unsigned char	*get_valid_input(char *input, size_t *size)
{
	unsigned char	*new;
	size_t			new_size;

	new_size = get_new_size(*size);
	(!(new = ft_memalloc(new_size))) ? ft_error("Error with malloc") : 0;
	ft_memcpy(new, input, *size);
	new[*size] |= 128;			// 10000000
	add_input_size(new + new_size - 8, *size * 8);
	*size = new_size;
	return (new);
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
	size_t			i;			//	counter for 512 blocks
	size_t			blocks_len;	//	quantity of 512 blocks

	hashed = get_valid_input(input, &size);
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
