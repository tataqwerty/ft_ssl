#include <ft_ssl.h>

static void		digest_init(unsigned int digest[])
{
	digest[0] = 0x6a09e667;
	digest[1] = 0xbb67ae85;
	digest[2] = 0x3c6ef372;
	digest[3] = 0xa54ff53a;
	digest[4] = 0x510e527f;
	digest[5] = 0x9b05688c;
	digest[6] = 0x1f83d9ab;
	digest[7] = 0x5be0cd19;
}

unsigned char	*sha256_hash(char *input, size_t size)
{
	unsigned int	digest[8];

	digest_init(digest);
	
	return (ft_strdup(input));
}
