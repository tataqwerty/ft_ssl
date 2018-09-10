#include <ft_ssl.h>

char	*get_input_value()
{

}

char	parse_arg(int ac, char *av[], int *i, t_md5 *flags)
{
	char	*s;
	char	*input_value;
	char	*hashed_value;

	s = av[*i];
	if (ft_strequ(s, "--") || *s != '-')
		return (0);
	s++;
	// while (1)
	// {
	// 	if ((*i + 1) < ac)
	// 		input_value = get_input_value(&s, av[*i + 1], flags);
	// 	else
	// 		input_value = get_input_value(&s, NULL, flags);
	// 	if (input_value)
	// 	{
	// 		hashed_value = hash(input_value);
	// 		output(input_value, hashed_value, flags);
	// 		ft_memdel(&input_value);
	// 		ft_memdel(&hashed_value);
	// 	}
	// 	else
	// 		break ;
	// }
	while ((input_value = get_input_value(&s, ac, av, i, flags)))
	{
		hashed_value = hash(input_value);
		output(input_value, hashed_value, flags);
		ft_memdel(&input_value);
		ft_memdel(&hashed_value);
	}
	return (1);
}

void			md5(int ac, char *av[])
{
	t_md5	*flags;
	int		i;

	flags = (t_md5 *)ft_memalloc(sizeof(t_md5 *));
	(!flags) ? ft_error("ERROR MALLOC") : 0;
	i = 2;
	while (i < ac)
	{
		if (!parse_arg(ac, av, &i, flags))
			break ;
		i++;
	}
	// while (i < ac)
	// {
	// 	FILES
	// 	i++;
	// }
}
