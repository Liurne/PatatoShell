/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 22:42:42 by jcoquard          #+#    #+#             */
/*   Updated: 2022/11/24 14:03:28 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dl;
	size_t	sl;
	size_t	i;

	dl = ft_strlen(dst);
	sl = ft_strlen(src);
	i = -1;
	if (dstsize <= 0)
		return (sl);
	while (++i < sl && dl + i < dstsize - 1)
		dst[(dl) + i] = src[i];
	dst[(dl) + i] = '\0';
	if (dl > dstsize)
		return (sl + dstsize);
	return (dl + sl);
}
