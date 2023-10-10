/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 23:34:25 by liurne            #+#    #+#             */
/*   Updated: 2023/10/05 16:57:42 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_addchar(char *str, char c)
{
	int	len;
	char *res;

	len = 0;
	if (str && *str)
		len = ft_strlen(str);
	res = ft_calloc(len + 2, sizeof(char));
	if (!res)
		return(ft_dprintf(2, "%s",  ERR_MALLOC), NULL);
	if (str && *str)
		ft_strlcpy(res, str, len + 1);
	res[len] = c;
	if (str && *str)
		free (str);
	return (res);
}

int	ft_striswhitespace(char *str)
{
	while(*str)
	{
		if (!ft_iswhitespace(*str))
			return (0);
		str++;
	}
	return (1);
}
