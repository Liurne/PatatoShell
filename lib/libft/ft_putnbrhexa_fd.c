/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrhexa_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 15:41:53 by jcoquard          #+#    #+#             */
/*   Updated: 2023/05/31 15:56:13 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbrhexa_fd(unsigned long long nbr, char *base, int fd)
{
	int	len;

	len = 0;
	if (nbr > 15)
	{
		len += ft_putnbrhexa_fd(nbr / 16, base, fd);
		len += ft_putnbrhexa_fd(nbr % 16, base, fd);
	}
	else
		len += write(fd, &base[nbr % 16], 1);
	return (len);
}
