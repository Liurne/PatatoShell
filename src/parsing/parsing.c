/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:53:21 by liurne            #+#    #+#             */
/*   Updated: 2023/10/23 18:25:13 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


//Mettre un pointeur sur env dans les cmd!!

int	find_error(char *line)
{
	t_quote	quote;
	int		tmp;

	ft_bzero(&quote, sizeof(t_quote));
	if (is_emptybpipe(line))
		return (ft_dprintf(2, ERR_PIPE1), g_rvalue = 2, 2);
	while (*line)
	{
		tmp = 1;
		manage_quote(*line, &quote);
		if (*line == '|' && !quote.s && !quote.d && (!*(line + 1)
				|| ft_striswspace(line + 1)))
			return (ft_dprintf(2, ERR_PIPE2), g_rvalue = 2, 2);
		if ((*line == '<' || *line == '>')
			&& is_bracketvalid(line, *line, &tmp) && !quote.s && !quote.d)
			return (2);
		line += tmp;
	}
	if (quote.s)
		return (ft_dprintf(2, ERR_SQUOTE), g_rvalue = 2, 2);
	if (quote.d)
		return (ft_dprintf(2, ERR_DQUOTE), g_rvalue = 2, 2);
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
	while (i < shell->prompt.nb_cmds)
	{
		shell->prompt.cmds[i].cmd = trim(shell, &(shell->prompt.cmds[i]),
				shell->prompt.cmds[i].cmd);
		//printf("%s\n", shell->prompt.cmds[i].cmd);
		pars_redir(&(shell->prompt.cmds[i]));
		i++;
	}
	exec(shell, &(shell->prompt.cmds[0]));
	free_cmds(shell);
	return (0);
}
