/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:05:04 by liurne            #+#    #+#             */
/*   Updated: 2023/11/03 15:41:25 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//executer les heredocs avant l'exec (avant le fork et le while)

void	free_child(t_data *shell, t_cmd *cmd, int pid)
{
	if (cmd->args)
		free_dtab(cmd->args);
	if (cmd->exec)
		free(cmd->exec);
	if (cmd->infile)
		close(cmd->infile);
	if (cmd->outfile)
		close(cmd->outfile);
	if (cmd->pipe[0])
		close(cmd->pipe[0]);
	if (cmd->pipe[1])
		close(cmd->pipe[1]);
	if (!pid)
	{
		free(shell->prompt.line);
		free_cmds(shell);
		free_dtab(shell->env);
	}
}

int	exec_child(t_data *shell, t_cmd *cmd)
{
	cmd->exec = get_cmd(shell, cmd->args[0]);
	if (!cmd->exec)
	{
		ft_dprintf(2, "patate: command '%s' not found\n", cmd->args[0]);
		return (free_child(shell, cmd, 0), 1);
	}
	if (execve(cmd->exec, cmd->args, shell->env) == -1)
	{
		ft_dprintf(2, "patate: command '%s' not found\n", cmd->args[0]);
		return (free_child(shell, cmd, 0), 1);
	}
	return (ft_dprintf(2, "patate: command '%s' not found\n", cmd->args[0]),
		free_child(shell, cmd, 0), 0);
}

int	exec(t_data *shell, t_cmd *cmd)
{
	pid_t	pid;

	if (pars_redir(cmd))
		return (free_child(shell, cmd, 1), 1);
	if (striswspace(cmd->cmd))
		return (free_child(shell, cmd, 1), 0);
	if (splitargs(cmd, cmd->cmd))
		return (free_child(shell, cmd, 1), 1);
//	if(shell->prompt.nb_cmds == 1)
//	
	pid = fork();
	if (pid == -1)
		return (1);
	if (!pid)
		exit(exec_child(shell, cmd));
	if (pid)
		waitpid(pid, NULL, 0);
	free_child(shell, cmd, 1);
	return (0);
}
