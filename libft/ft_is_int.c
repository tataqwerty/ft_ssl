/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 15:31:47 by tkiselev          #+#    #+#             */
/*   Updated: 2018/08/27 16:49:42 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			ft_is_int(char *str)
{
	long int	res;

	if (!str)
		return (0);
	else if (ft_strequ(str, "-2147483648"))
		return (1);
	res = 0;
	(*str == '-' || *str == '+') ? str++ : 0;
	if (ft_strlen(str) == 0)
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		if ((res == 214748364 && *str >= '8') || res > 214748365)
			return (0);
		res = res * 10 + *str - '0';
		str++;
	}
	return ((*str == '\0') ? 1 : 0);
}
