/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_sha_algo_staff.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 16:45:29 by tkiselev          #+#    #+#             */
/*   Updated: 2018/09/23 16:45:30 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

static size_t	get_new_size(size_t size)
{
	size++;
	while ((size % 64) != 56)
		size++;
	size += 8;
	return (size);
}

/*
** Adds padding bits (1 + 000...)
** Adds length (last 8 bytes)
*/

unsigned char	*md5_sha_get_padded_input(char *input, size_t *size)
{
	unsigned char	*new;
	size_t			new_size;

	new_size = get_new_size(*size);
	(!(new = ft_memalloc(new_size))) ? ft_error("Error with malloc") : 0;
	ft_memcpy(new, input, *size);
	new[*size] |= 128;
	*size = new_size;
	return (new);
}

void			md5_sha_create_hash(unsigned char **hash,
				unsigned int buffers[], int hash_size, int buffers_n)
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

void			copy_16_words(unsigned int w[], unsigned char *hashed)
{
	unsigned char	i;

	i = 0;
	while (i < 16)
	{
		ft_memcpy((unsigned char *)&w[i], hashed, 4);
		i++;
		hashed += 4;
	}
}

void			init_buffers(unsigned int buffers[], unsigned int array[])
{
	buffers[0] = array[0];
	buffers[1] = array[1];
	buffers[2] = array[2];
	buffers[3] = array[3];
	buffers[4] = array[4];
	buffers[5] = array[5];
	buffers[6] = array[6];
	buffers[7] = array[7];
}
