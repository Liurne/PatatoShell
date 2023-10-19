/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 00:44:04 by liurne            #+#    #+#             */
/*   Updated: 2023/10/19 18:56:17 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strbdup(char *line, size_t s, size_t e)
{
	size_t	len;
	char	*res;
	size_t	i;

	len = e - s + 1;
	if (!line || len < 2 || s > e || ft_strlen(line) < e)
		return (NULL);
	res = ft_calloc(len, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i + s < e)
	{
		res[i] = line[e + i];
		i++;
	}
	return (res);
}
