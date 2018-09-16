#include <ft_ssl.h>

void	ft_error(char *s)
{
	ft_printf("%s\n", s);
	exit(0);
}

static void	str_join_free(char **dest, char *src, size_t dest_len, int src_len)
{
	char	*new;
	int		i;
	int		j;

	if (!(new = ft_strnew(dest_len + src_len)))
		ft_error("Error with malloc");
	i = 0;
	while (i < dest_len)
	{
		new[i] = (*dest)[i];
		i++;
	}
	j = 0;
	while (j < src_len)
	{
		new[i] = src[j];
		i++;
		j++;
	}
	free(*dest);
	*dest = new;
}

char	*read_data(int fd, size_t *size)
{
	char	buf[BUFF_SIZE];
	char	*data;
	int		tmp;

	data = ft_strdup("");
	ft_bzero(buf, BUFF_SIZE);
	while ((tmp = read(fd, buf, BUFF_SIZE)) > 0)
	{
		str_join_free(&data, buf, *size, tmp);
		*size += tmp;
		ft_bzero(buf, BUFF_SIZE);
	}
	return data;
}
