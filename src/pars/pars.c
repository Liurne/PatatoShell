/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:06:21 by jcoquard          #+#    #+#             */
/*   Updated: 2023/06/28 14:14:00 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd(t_data *prompt)
{
	int	res;
	int	i;

	res = 1;
	i = -1;
	while (prompt->line[++i])
		if (prompt->line[i] == '|')
			res++;
	return (res);
}

int	count_quote(t_data *prompt)
{
	int	dquote;
	int	squote;
	int	i;

	i = -1;
	dquote = 0;
	squote = 0;
	while (prompt->line[++i])
	{
		if (prompt->line[i] == '\'' && )
	}
}