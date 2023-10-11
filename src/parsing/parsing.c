/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:53:21 by liurne            #+#    #+#             */
/*   Updated: 2023/10/10 14:59:13 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_error(char *line)
{
	int	squote;
	int	dquote;
	int	tmp;
	
	squote = 0;
	dquote = 0;
	if(is_emptybpipe(line))
		return (ft_dprintf(2, ERR_PIPE1), 2);
	while (*line)
	{
		tmp = 1;
		manage_quote(*line, &squote, &dquote);
		if (*line == '|' && (!*(line + 1) || ft_striswspace(line + 1)))
			return(ft_dprintf(2, ERR_PIPE2), 2);
		if ((*line == '<' || *line == '>') && is_bracketvalid(line, *line, &tmp))
			return (2);
		line += tmp;
	}
	if (squote)
		return (ft_dprintf(2, ERR_SQUOTE), 2);
	if (dquote)
		return (ft_dprintf(2, ERR_DQUOTE), 2);
	return (0);
}

int	pars(t_data *shell)
{
	unsigned int	i;
	
	i = 0;
	if (ft_striswspace(shell->prompt.line))
		return (0);
	if (find_error(shell->prompt.line))
		return (2);
	if (ft_splitcmds(shell, shell->prompt.line))
		return (1);
	(void)i;
	while (i < shell->prompt.nb_cmds)
	{
		pars_redir(&(shell->prompt.cmds[i]));
		i++;
	}
	free_cmds(shell);
	return (0);
}