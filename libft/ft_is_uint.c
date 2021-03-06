/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_uint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 15:31:47 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/14 17:52:47 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			ft_is_uint(char *str)
{
	long int	res;

	if (!str || ft_strlen(str) == 0)
		return (0);
	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		if ((res == 429496729 && *str >= '6') || res > 429496730)
			return (0);
		res = res * 10 + *str - '0';
		str++;
	}
	return ((*str == '\0') ? 1 : 0);
}
