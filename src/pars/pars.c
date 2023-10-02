/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:06:21 by jcoquard          #+#    #+#             */
/*   Updated: 2023/06/29 16:39:15 by jcoquard         ###   ########.fr       */
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
		if (prompt->line[i] == '\'' && !dquote%2)
			squote++;
		if (prompt->line[i] == '\"' && !squote%2)
			dquote++;
	}
	if (dquote%2 || squote%2)
		return (1);
	return (0);
}