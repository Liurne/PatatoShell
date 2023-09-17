/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:58:59 by jcoquard          #+#    #+#             */
/*   Updated: 2023/06/03 19:24:26 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "stdio.h"

static char	*append_str(char *s1, char *s2)
{
	char *res;

	res = NULL;
	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	if (!res)
		return (NULL);
	return (res);
	
}

int	ft_dprintf(int fd, const char *str, ...)
{
	va_list		ap;
	long int	i;
	char		*res;

	i = -1;
	if (!str)
		return (0);
	if (write(1, 0, 0) == -1)
		return (-1);
	res = NULL;
	va_start(ap, str);
	while (str[++i])
	{
		if (str[i] == '%' && *(str + i + 1))
		{
			res = append_str(res, ft_strndup(str, i));
			str += i + 1;
			i = 0;
			res = append_str(res, get_arg(str, ap));
			str++;
		}
	}
	res = append_str(res, ft_strndup(str, i));
	if (!res)
		return (va_end(ap), -1);
	i = write(fd, res, ft_strlen(res));
	va_end(ap);
	return (free(res), (int)i);
}
