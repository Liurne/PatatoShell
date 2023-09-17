/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 22:42:09 by jcoquard          #+#    #+#             */
/*   Updated: 2022/11/24 14:01:56 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_recurs_it(long int n, char *res, int l)
{
	if (n < 0)
	{
		n *= -1;
		res[0] = '-';
	}
	if (n > 0)
	{
		res[l - 1] = '0' + n % 10;
		l--;
		ft_recurs_it(n / 10, res, l);
	}
}

char	*ft_itoa(int n)
{
	int		l;
	int		t;
	char	*res;

	l = 1;
	t = n;
	while (t > 9 || t < -9)
	{
		t /= 10;
		l++;
	}
	if (t < 0)
		l++;
	res = ft_calloc((l + 1), sizeof(char));
	if (!res)
		return (NULL);
	if (n == 0)
		res[0] = '0';
	else
		ft_recurs_it(n, res, l);
	return (res);
}
