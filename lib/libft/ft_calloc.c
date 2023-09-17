/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 22:40:40 by jcoquard          #+#    #+#             */
/*   Updated: 2022/11/24 12:50:48 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void		*res;

	if (size > 0 && count > SIZE_MAX / size)
		return (NULL);
	res = malloc(count * size);
	if (res)
	{
		ft_bzero(res, count * size);
		return (res);
	}
	return (NULL);
}
