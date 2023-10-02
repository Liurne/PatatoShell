/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 22:42:46 by jcoquard          #+#    #+#             */
/*   Updated: 2022/11/14 12:05:42 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	t;
	size_t	n;

	t = 0;
	n = 0;
	if (size != 0)
	{
		while (src[t] != '\0')
		{
			if (t < (size - 1))
			{
				dst[t] = src[t];
				n++;
			}
			t++;
		}
	}
	else
	{
		while (src[t] != '\0')
			t++;
		return (t);
	}
	dst[n] = '\0';
	return (t);
}
