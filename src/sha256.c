#include <ft_ssl.h>

static void		extend_words(unsigned int w[])
{
	unsigned int	tmp1;
	unsigned int	tmp2;
	unsigned char	i;

	i = 16;
	while (i < 64)
	{
		tmp1 = RIGHT_ROTATE(w[i-15], 7) ^ RIGHT_ROTATE(w[i-15], 18) ^ RIGHT_SHIFT(w[i-15], 3);
		tmp2 = RIGHT_ROTATE(w[i-2], 17) ^ RIGHT_ROTATE(w[i-2], 19) ^ RIGHT_SHIFT(w[i-2], 10);
		w[i] = w[i-16] + tmp1 + w[i-7] + tmp2;
		i++;
	}
}

static void	operation_switcher(unsigned int abcdefgh[], unsigned int w[], int i, unsigned int tmp[])
{
	unsigned int s0;
	unsigned int s1;
	unsigned int maj;
	unsigned int ch;

	s1 = RIGHT_ROTATE(abcdefgh[4], 6) ^ RIGHT_ROTATE(abcdefgh[4], 11) ^ RIGHT_ROTATE(abcdefgh[4], 25);
	ch = (abcdefgh[4] & abcdefgh[5]) ^ (~abcdefgh[4] & abcdefgh[6]);
	tmp[0] = abcdefgh[7] + s1 + ch + g_table_sha256_k[i] + w[i];
	s0 = RIGHT_ROTATE(abcdefgh[0], 2) ^ RIGHT_ROTATE(abcdefgh[0], 13) ^ RIGHT_ROTATE(abcdefgh[0], 22);
	maj = (abcdefgh[0] & abcdefgh[1]) ^ (abcdefgh[0] & abcdefgh[2]) ^ (abcdefgh[1] & abcdefgh[2]);
	tmp[1] = s0 + maj;
}

static void		array_map(unsigned int arr[], int arr_n, unsigned char bytes, size_t (*f)(size_t, unsigned char))
{
	int i;

	i = 0;
	while (i < arr_n)
	{
		arr[i] = f(arr[i], bytes);
		i++;
	}
}

static void		sha256_block_handler(unsigned char *hashed, unsigned int buffers[])
{
	unsigned int	w[64];
	unsigned int	abcdefgh[8];
	unsigned int	tmp[2];
	int				i;

	copy_16_words(w, hashed);
	array_map(w, 16, 4, reverse_bytes);	//	16 elements each of size of 4 bytes.
	extend_words(w);
	init_buffers(abcdefgh, buffers);
	i = -1;
	while (++i < 64)
	{
		operation_switcher(abcdefgh, w, i, tmp);
		init_buffers(abcdefgh, (unsigned int[]){
			tmp[0] + tmp[1], abcdefgh[0], abcdefgh[1], abcdefgh[2],
			abcdefgh[3] + tmp[0], abcdefgh[4], abcdefgh[5], abcdefgh[6]
		});
	}
	init_buffers(buffers, (unsigned int[]){
		buffers[0] + abcdefgh[0], buffers[1] + abcdefgh[1],
		buffers[2] + abcdefgh[2], buffers[3] + abcdefgh[3],
		buffers[4] + abcdefgh[4], buffers[5] + abcdefgh[5],
		buffers[6] + abcdefgh[6], buffers[7] + abcdefgh[7]
	});
}

unsigned char	*sha256_hash(char *input, size_t size)
{
	unsigned char	*hashed;
	unsigned int	buffers[8];
	size_t			input_size;
	size_t			i;
	size_t			blocks_len;

	input_size = reverse_bytes(size * 8, 8);
	hashed = md5_sha_get_padded_input(input, &size);
	ft_memcpy(hashed + size - 8, (unsigned char *)&input_size, 8);
	init_buffers(buffers, (unsigned int[]){
		0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A,
		0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19
	});
	i = 0;
	blocks_len = size / 64;
	while (i < blocks_len)
		sha256_block_handler(hashed + (i++ * 64), buffers);
	ft_memdel((void **)&hashed);
	array_map(buffers, 8, 4, reverse_bytes);	//	8 elements in array, each of size of 4 bytes.
	md5_sha_create_hash(&hashed, buffers, 64, 8);
	return (hashed);
}
