/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcpy_neg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:44:11 by liurne            #+#    #+#             */
/*   Updated: 2023/10/25 15:25:18 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	strcpy_neg(char *dst, const char *src, size_t size)
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
				dst[t] = -src[t];
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
