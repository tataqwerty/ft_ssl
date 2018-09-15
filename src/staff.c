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

char	*read_data(int fd)
{
	char	buf[BUFF_SIZE];
	char	*data;

	ft_bzero(buf, BUFF_SIZE);
	data = ft_strdup("");
	while (read(fd, buf, BUFF_SIZE) > 0)
	{
		data = ft_strjoinfree(data, buf, 1);
	}
	return (data);
}

void	hash_handler(char *input_value, void *flags, char *(*hash)(char *), void (*output)(char *, char *, void *))
{
	char	*hashed_value;

	ft_printf("===> %s", input_value);
	// hashed_value = hash(input_value);
	// output(input_value, hashed_value, flags);
	ft_strdel(&input_value);
	// ft_memdel(&hashed_value);
}
