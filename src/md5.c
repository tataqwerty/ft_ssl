#include <ft_ssl.h>

// static void			md5_parse(int ac, char *av[], void *flags)
// {

// }

// static void			md5_output(char *input_data, char *output_data, void *flags)
// {

// }

void			md5(t_command *command, int ac, char *av[])
{
	t_md5	*flags;

	flags = (t_md5 *)init_flags(sizeof(t_md5 *));
	ft_printf("%d\n", flags->q);
}
