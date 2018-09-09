#include <ft_ssl.h>

void	ft_error(char *s)
{
	ft_printf("%s\n", s);
	exit(0);
}

void	*init_flags(size_t size)
{
	void	*flags;

	flags = (void *)malloc(sizeof(void) * size);
	(!flags) ? ft_error("Error") : 0;
	ft_bzero(flags, sizeof(flags));
	return (flags);
}
