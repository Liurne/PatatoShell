/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 22:18:56 by jcoquard          #+#    #+#             */
/*   Updated: 2023/11/09 14:07:07 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*res;
	size_t	l;
	size_t	i;

	l = 0;
	if (!s)
		return (NULL);
	while (s[l])
		l++;
	res = (char *)malloc(sizeof(char) * (l + 1));
	if (res == NULL)
		return (NULL);
	i = -1;
	while (s[++i] && l != 0)
		res[i] = s[i];
	res[i] = '\0';
	return (res);
}
