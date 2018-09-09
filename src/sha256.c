#include <ft_ssl.h>

// static void			sha256_parse(int ac, char *av[], void *flags)
// {

// }

// static void			sha256_output(char *input_data, char *output_data, void *flags)
// {

// }

void			sha256(t_command *command, int ac, char *av[])
{
	t_sha_256	*flags;

	flags = (t_sha_256 *)init_flags(sizeof(t_sha_256 *));
	ft_printf("%d\n", flags->q);
}
