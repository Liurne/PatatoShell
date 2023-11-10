/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:16:37 by edecoste          #+#    #+#             */
/*   Updated: 2023/11/10 13:36:30 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_overflow(long long n, int last, int sign)
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

long long	ft_atoll(const char *str)
{
	size_t		i;
	long long	m;
	long long	res;

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
