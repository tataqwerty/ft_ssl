#include <ft_ssl.h>

void	sha_256_output(char *input_value, char *hashed_value, void *flags)
{
	flags = (t_sha_256 *)flags;

}

char	*sha_256_hash(char *input)
{
	return (NULL);
}

/*
** @param flags - pointer to a structure in which I save all the flags that appears.
** @param flag_output - represents whether something was outputed or not, during parsing flags or parsing files (just because I need to loop to get input data from user and hash it).
** @param i - counter for av (arguments);
*/

void		sha_256(int ac, char *av[])
{
	t_sha_256	*flags;
	char	flag_output;
	int		i;

	flags = ft_memalloc(sizeof(t_sha_256 *));
	(!flags) ? ft_error("Error: something wrong with malloc") : 0;
	i = 2;
	flag_output = 0;
	flag_output |= sha_256_parse_flags(av, ac, &i, flags);
	flag_output |= sha_256_parse_files(av, ac, &i, flags);
	if (flag_output == 0)
		hash_handler(read_data(0), flags, sha_256_hash, sha_256_output);
}
