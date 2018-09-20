#include <ft_ssl.h>

static void	copy_4_bytes(unsigned char *dest, unsigned char *src)
{
	dest[0] = src[0];
	dest[1] = src[1];
	dest[2] = src[2];
	dest[3] = src[3];
}

static void	copy_16_words(unsigned int M[], unsigned char *hashed)
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

void		md5_block_handler(unsigned char *hashed, unsigned int buffers[])
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
		abcd[1] += LEFT_ROTATE(F, g_table_s[i]);
	}
	buffers[0] += abcd[0];
	buffers[1] += abcd[1];
	buffers[2] += abcd[2];
	buffers[3] += abcd[3];
}
