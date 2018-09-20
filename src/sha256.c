#include <ft_ssl.h>

// static void	operation_switcher(unsigned int abcd[], unsigned int *F, unsigned int *g, unsigned int i)
// {
	
// }

static void		sha256_block_handler(unsigned char *hashed, unsigned int buffers[])
{
	unsigned int	M[16];
	int				i;

	copy_16_words(M, hashed);
	i = -1;
	while (++i < 64)
	{
		// operation_switcher();
	}
}

static void	init_buffers(unsigned int buffers[])
{
	buffers[0] = 0x6A09E667;
	buffers[1] = 0xBB67AE85;
	buffers[2] = 0x3C6EF372;
	buffers[3] = 0xA54FF53A;
	buffers[4] = 0x510E527F;
	buffers[5] = 0x9B05688C;
	buffers[6] = 0x1F83D9AB;
	buffers[7] = 0x5BE0CD19;
}

unsigned char	*sha256_hash(char *input, size_t size)
{
	unsigned char	*hashed;
	unsigned int	buffers[8];
	size_t			i;
	size_t			blocks_len;

	hashed = md5_sha_get_padded_input(input, &size);
	i = 0;
	init_buffers(buffers);
	blocks_len = size / 64;
	while (i < blocks_len)
		sha256_block_handler(hashed + (i++ * 64), buffers);
	ft_memdel((void **)&hashed);
	md5_sha_create_hash(&hashed, buffers, 64, 8);
	return (hashed);
}
