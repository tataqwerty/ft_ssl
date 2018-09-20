#include <ft_ssl.h>

static size_t			get_new_size(size_t size)
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

unsigned char		*md5_sha_get_padded_input(char *input, size_t *size)
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

void				md5_sha_create_hash(unsigned char **hash, unsigned int buffers[], int hash_size, int buffers_n)
{
	unsigned char	*base;
	unsigned char	*tmp;
	unsigned char	i;
	unsigned char	j;
	unsigned char	k;

	base = (unsigned char *)"0123456789abcdef";
	(!(*hash = ft_memalloc(hash_size + 1))) ? ft_error("Error with malloc") : 0;
	i = 0;
	j = 0;
	while (i < buffers_n)
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

void	copy_16_words(unsigned int M[], unsigned char *hashed)
{
	unsigned char	i;

	i = 0;
	while (i < 16)
	{
		ft_memcpy((unsigned char *)&M[i], hashed, 4);
		i++;
		hashed += 4;
	}
}
