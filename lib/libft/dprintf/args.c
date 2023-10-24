/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:54:18 by liurne            #+#    #+#             */
/*   Updated: 2023/10/19 18:54:40 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*get_char(char c)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * 2);
	if (!res)
		return (NULL);
	res[0] = c;
	res[1] = '\0';
	return (res);
}

static unsigned int	rec_hexa(unsigned int nb)
{
	unsigned int	len;

	len = 0;
	if (nb > 15)
	{
		len += rec_hexa(nb / 16);
		len += rec_hexa(nb % 16);
	}
	else
		len++;
	return (len);
}

static void	fill_hexa(unsigned int nb, char *base, char *res)
{
	if (nb > 15)
	{
		fill_hexa(nb / 16, base, res++);
		fill_hexa(nb % 16, base, res++);
	}
	else
		*res = base[nb % 16];
}

static char	*get_hexa(unsigned int nb, char *base)
{
	unsigned int	len;
	char			*res;

	len = rec_hexa(nb);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = '\0';
	fill_hexa(nb, base, res);
	return (res);
}

char	*get_arg(const char *str, va_list ap)
{
	if (*str == 'c')
		return (get_char((char)va_arg(ap, int)));
	if (*str == '%')
		return (get_char('%'));
	if (*str == 's')
		return (ft_strdup(va_arg(ap, char *)));
	if (*str == 'i' || *str == 'd')
		return (ft_itoa(va_arg(ap, int)));
	if (*str == 'x')
		return (get_hexa(va_arg(ap, unsigned int), "0123456789abcdef"));
	if (*str == 'X')
		return (get_hexa(va_arg(ap, unsigned int), "0123456789ABCDEF"));
	if (*str == 'u')
		return (ft_itoa(va_arg(ap, unsigned int)));
	return (0);
}
