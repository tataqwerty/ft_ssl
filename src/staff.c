#include <ft_ssl.h>

void	ft_error(char *s)
{
	ft_printf("%s\n", s);
	exit(0);
}

void	usage(void)
{
	ft_printf("usage: md5 [-pqrtx] [-s string] [files ...]\n");
	exit(0);
}
