/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:16:59 by jcoquard          #+#    #+#             */
/*   Updated: 2023/06/03 19:15:50 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*res;
	size_t	l;
	size_t	i;

	l = 0;
	while (s[l])
		l++;
	if (l < n || n == 0)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (n + 1));
	if (res == NULL)
		return (NULL);
	i = -1;
	while (s[++i] && i < n)
		res[i] = s[i];
	res[i] = '\0';
	return (res);
}
