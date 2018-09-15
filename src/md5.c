#include <ft_ssl.h>

char			parse_flags(int ac, char *av[], int *i, t_md5 *flags)
{
	char	*s;

	s = av[*i];
	if (ft_strequ(s, "--") || *s != '-')
		return (0);	// Заканчиваем парсинг флагов.
	s++;
	while (*s)
	{
		if (*s == 'q')
			flags->q = 1;
		else if (*s == 'r')
			flags->r = 1;
		else if (*s == 'p')
		{
			input_value = read_data(0);
			hashed_value = hash(input_value);
			output(input_value, hashed_value);
			ft_memdel(&input_value);
			ft_memdel(&hashed_value);
		}
		else if (*s == 's')
		{
			if (ft_strlen(s) > 1)	//	After character 's' comes another characters.
			{
				input_value = s + 1;
				hashed_value = hash(input_value);
				output(input_value, hashed_value);
				ft_memdel(&hashed_value);
			}
			else if ((*i + 1) < ac)
			{
				(*i)++;
				input_value = av[*i];
				hashed_value = hash(input_value);
				output(input_value, hashed_value);
				ft_memdel(&hashed_value);
			}
			else
				ft_error("Error");
			return (1);
		}
		s++;
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
		if (!parse_flags(ac, av, &i, flags))
			break ;
		i++;
	}
	// while (i < ac)
	// {
	// 	FILES
	// 	i++;
	// }
}
