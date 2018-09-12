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
	char	*line;
	char	*data;

	line = NULL;
	data = ft_strdup("");
	while (get_next_line(fd, &line) > 0)
	{
		line = ft_strjoinfree(line, "\n", 1);
		data = ft_strjoinfree(data, line, 3);
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
