/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:05:37 by jcoquard          #+#    #+#             */
/*   Updated: 2023/11/29 18:11:17 by liurne           ###   ########.fr       */
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

void	clear_proc(t_data *shell, int pid)
{
	if (!pid)
	{
		if (shell->prompt.line)
			free(shell->prompt.line);
		free_cmds(shell);
		if (shell->env)
			free_dtab(shell->env);
		rl_clear_history();
	}
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
		shell->prompt.cmds[i].cmd = expand(shell, shell->prompt.cmds[i].cmd);
		if (!shell->prompt.cmds[i].cmd)
			return (free_cmds(shell), 2);
		if (pars_heredoc(shell, &(shell->prompt.cmds[i])))
			return (free_cmds(shell), 2);
	}
	if (!g_rvalue)
		exec(shell, shell->prompt.cmds);
	free_cmds(shell);
	return (0);
}
