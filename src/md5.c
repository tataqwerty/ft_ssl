#include <ft_ssl.h>

void	add_one_byte(char **input, size_t *size, unsigned char byte)
{
	char	*new;
	size_t	i;

	if (!(new = ft_strnew(*size + 1)))
		ft_error("Error with malloc");
	i = 0;
	while (i < *size)
	{
		new[i] = (*input)[i];
		i++;
	}
	new[i] |= byte;
	free(*input);
	*input = new;
	(*size)++;
}

void	align_input(char **input, size_t *size)
{
	add_one_byte(input, size, 128);
	while ((*size % 64) != 56)
		add_one_byte(input, size, 0);
}

void	add_input_size(char **input, size_t *size, size_t input_size)
{
	char			*new;
	unsigned char	*input_size_ptr;
	size_t			i;
	unsigned char	j;

	if (!(new = ft_strnew(*size + 8)))
		ft_error("Error with malloc");
	i = 0;
	while (i < *size)
	{
		new[i] = (*input)[i];
		i++;
	}
	input_size_ptr = (unsigned char *)&input_size;
	while (j < 8)
	{
		new[i + j] = input_size_ptr[j];
		j++;
	}
	*size += 8;
	free(*input);
	*input = new;
}

char	*md5_hash(char *input, size_t size)
{
	char	*hashed;
	size_t	input_size;

	input_size = size;
	hashed = ft_strdup(input);			//	doesn't work with binaries.
	align_input(&hashed, &size);
	add_input_size(&hashed, &size, input_size);
	
	return (hashed);
}
