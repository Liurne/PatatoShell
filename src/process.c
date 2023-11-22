/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:05:37 by jcoquard          #+#    #+#             */
/*   Updated: 2023/11/22 15:27:16 by jcoquard         ###   ########.fr       */
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

void	clear_proc(t_data *shell, t_cmd *cmd, int pid)
{
	if (cmd->args)
		free_dtab(cmd->args);
	if (cmd->exec)
		free(cmd->exec);
	if (cmd->infile)
		close(cmd->infile);
	if (cmd->outfile)
		close(cmd->outfile);
	if (cmd->pipe[1])
		close(cmd->pipe[1]);
	if (!pid)
	{
		if (cmd->pipe[0])
			close(cmd->pipe[0]);
		free(shell->prompt.line);
		free_cmds(shell);
		if (shell->env)
			free_dtab(shell->env);
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
		//if (pars_heredoc(shell, &(shell->prompt.cmds[i])))
		//	return (free_cmds(shell), 2);
		//exec(shell, &(shell->prompt.cmds[i]));
	}
	free_cmds(shell);
	return (0);
}
