/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:05:37 by jcoquard          #+#    #+#             */
/*   Updated: 2023/11/03 15:40:21 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_rval(int val, char *error)
{
	if (error)
		ft_dprintf(2, "%s", error);
	g_rvalue = val;
	return (val);
}

int	process(t_data *shell)
{
	unsigned int	i;

	i = -1;
	if (striswspace(shell->prompt.line))
		return (0);
	if (pars_line(shell->prompt.line))
		return (2);
	if (splitcmds(shell, shell->prompt.line))
		return (2);
	while (++i < shell->prompt.nb_cmds)
	{
		shell->prompt.cmds[i].cmd = expand(shell, &(shell->prompt.cmds[i]),
				shell->prompt.cmds[i].cmd);
		if (!shell->prompt.cmds[i].cmd)
			return (free_cmds(shell), 2);
//		if (pars_heredoc(&(shell->prompt.cmds[i])))
//			return (free_cmds(shell), 2);
		exec(shell, &(shell->prompt.cmds[i]));
	}
	free_cmds(shell);
	return (0);
}
