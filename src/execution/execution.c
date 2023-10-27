/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:05:04 by liurne            #+#    #+#             */
/*   Updated: 2023/10/27 16:33:42 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_child(t_data *shell, t_cmd *cmd)
{
	if (cmd->args)
		free_dtab(cmd->args);
	if (cmd->exec)
		free(cmd->exec);
	free(shell->prompt.line);
	free_cmds(shell);
	free_dtab(shell->env);
}

int	exec_child(t_data *shell, t_cmd *cmd)
{
	if (splitargs(cmd, cmd->cmd))
		return (free_child(shell, cmd), 1);
	cmd->exec = get_cmd(shell, cmd->args[0]);
	if (!cmd->exec)
	{
		ft_dprintf(2, "patate: command '%s' not found\n", cmd->args[0]);
		return (free_child(shell, cmd), 1);
	}
	if (execve(cmd->exec, cmd->args, shell->env) == -1)
	{
		ft_dprintf(2, "patate: command '%s' not found\n", cmd->args[0]);
		return (free_child(shell, cmd), 1);
	}
	return (ft_dprintf(2, "patate: command '%s' not found\n", cmd->args[0]), free_child(shell, cmd), 0);
}

int	exec(t_data *shell, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (!pid)
		exit(exec_child(shell, cmd));
	if (pid)
		waitpid(pid, NULL, 0);
	return (0);
}

