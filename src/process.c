/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:05:37 by jcoquard          #+#    #+#             */
/*   Updated: 2023/11/24 17:49:42 by jcoquard         ###   ########.fr       */
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
	printf("nb cmd: %d\n", shell->prompt.nb_cmds);
	while (++i < shell->prompt.nb_cmds)
	{
		printf("id: %d\n", shell->prompt.cmds[i].id);
		shell->prompt.cmds[i].cmd = expand(shell, shell->prompt.cmds[i].cmd);
		if (!shell->prompt.cmds[i].cmd)
			return (free_cmds(shell), 2);
		if (pars_heredoc(shell, &(shell->prompt.cmds[i])))
			return (free_cmds(shell), 2);
	}
	i = -1;
	while (++i < shell->prompt.nb_cmds)
		exec(shell, &(shell->prompt.cmds[i]));
	free_cmds(shell);
	return (0);
}
