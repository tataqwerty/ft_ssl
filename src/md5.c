#include <ft_ssl.h>

static void	operation_switcher(unsigned int abcd[], unsigned int *F, unsigned int *g, unsigned int i)
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

static void		md5_block_handler(unsigned char *hashed, unsigned int buffers[])
{
	unsigned int	abcd[4];
	unsigned int	w[16];
	unsigned int	F;
	unsigned int	g;
	int				i;

	copy_16_words(w, hashed);
	abcd[0] = buffers[0];
	abcd[1] = buffers[1];
	abcd[2] = buffers[2];
	abcd[3] = buffers[3];
	i = -1;
	while (++i < 64)
	{
		operation_switcher(abcd, &F, &g, i);
		F = F + abcd[0] + g_table_md5_sha_t[i] + w[g];
		abcd[0] = abcd[3];
		abcd[3] = abcd[2];
		abcd[2] = abcd[1];
		abcd[1] += LEFT_ROTATE(F, g_table_md5_sha_s[i]);
	}
	buffers[0] += abcd[0];
	buffers[1] += abcd[1];
	buffers[2] += abcd[2];
	buffers[3] += abcd[3];
}

unsigned char		*md5_hash(char *input, size_t size)
{
	unsigned char	*hashed;
	unsigned int	buffers[4];
	size_t			input_size;
	size_t			i;			//	counter for 512 blocks
	size_t			blocks_len;	//	quantity of 512 blocks

	input_size = size * 8;
	hashed = md5_sha_get_padded_input(input, &size);
	ft_memcpy(hashed + size - 8, (unsigned char *)&input_size, 8);
	buffers[0] = 0x67452301;
	buffers[1] = 0xefcdab89;
	buffers[2] = 0x98badcfe;
	buffers[3] = 0x10325476;
	i = 0;
	blocks_len = size / 64;
	while (i < blocks_len)
		md5_block_handler(hashed + (i++ * 64), buffers);
	ft_memdel((void **)&hashed);
	md5_sha_create_hash(&hashed, buffers, 32, 4);
	return (hashed);
}

