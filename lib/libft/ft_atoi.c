/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:19:14 by jcoquard          #+#    #+#             */
/*   Updated: 2022/11/24 16:17:08 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_overflow(long int n, int last, int sign)
{
	if (sign * n != sign * (n * 10 + last) / 10)
	{
		if (sign * (n * 10 + last) / 10 < 0)
			return (-1);
		else
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	size_t		i;
	long int	m;
	long int	res;

	res = 0;
	i = 0;
	m = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		m = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (ft_check_overflow(res, str[i] - 48, m) != 1)
			return (ft_check_overflow(res, str[i] - 48, m));
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * m);
}
