/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strpos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:14:17 by jcoquard          #+#    #+#             */
/*   Updated: 2023/11/16 17:24:08 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*strpos(char *str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] < 0)
			str[i] = str[i] * -1;
		i++;
	}
	return (str);
}
