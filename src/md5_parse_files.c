#include <ft_ssl.h>

static void	file_handler(char *file_name, t_md5 *flags)
{
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("md5: %s: No such file or directory\n", file_name);
		exit(0);
	}
	else if (read(fd, NULL, 0) < 0)
	{
		ft_printf("md5: %s: Is a directory\n", file_name);
		exit(0);
	}
	hash_handler(read_data(fd), flags, md5_hash, md5_output);
	close(fd);
}

char		md5_parse_files(char *av[], int ac, int *i, t_md5 *flags)
{
	char	flag_output;

	flag_output = 0;
	while (*i < ac)
	{
		file_handler(av[*i], flags);
		flag_output = 1;
		(*i)++;
	}
	return (flag_output);
}
