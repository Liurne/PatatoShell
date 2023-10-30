/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:55:16 by liurne            #+#    #+#             */
/*   Updated: 2023/10/23 17:10:40 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_striswspace(char *str)
{
	while (*str)
	{
		if (!ft_iswhitespace(*str))
			return (0);
		str++;
	}
	return (1);
}

int	manage_quote(char c, t_quote *quote)
{
	if (c == '\'' && !quote->d)
		quote->s = -(quote->s) + 1;
	if (c == '"' && !quote->s)
		quote->d = -(quote->d) + 1;
	if ((c == '\'' && !quote->d) || (c == '"' && !quote->s))
		return (1);
	return (0);
}

void	free_dtab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}