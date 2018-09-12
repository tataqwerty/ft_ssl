#include <ft_ssl.h>

static void	file_handler(char *file_name, t_sha_256 *flags)
{
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("sha256: %s: No such file or directory\n", file_name);
		exit(0);
	}
	else if (read(fd, NULL, 0) < 0)
	{
		ft_printf("sha256: %s: Is a directory\n", file_name);
		exit(0);
	}
	hash_handler(read_data(fd), flags, sha_256_hash, sha_256_output);
	close(fd);
}

char		sha_256_parse_files(char *av[], int ac, int *i, t_sha_256 *flags)
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
