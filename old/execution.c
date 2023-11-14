/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:05:04 by liurne            #+#    #+#             */
/*   Updated: 2023/11/14 17:51:45 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//pour les builtins 
//faire en sorte que tout soit free dans les builtins
//detecter pour une seule commande pour cd et exit
//exec builtin return 0 si pas 1 si oui 2 si error
//revoir le echo sur les options et sur les arg pour permettrent de tout free
//revoir le exit sur les parametre de fct pour tout free et tester le truc
//env tester la commande surement changer les paramettre aussi
// exec process : redir, si cmd vide, split arg, si 1 cmd test builtin, sinon exec fork, verifier pipe, valeur de retour des process avec le waitpid


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
	if (!pid)
	{
		if (cmd->pipe[0])
			close(cmd->pipe[0]);
		if (cmd->pipe[1])
			close(cmd->pipe[1]);
		free(shell->prompt.line);
		free_cmds(shell);
		free_dtab(shell->env);
	}
}

int	exec_child(t_data *shell, t_cmd *cmd)
{
	exec_builtins(shell, cmd, 0);
	cmd->exec = get_cmd(shell, cmd->args[0]);
	if (!cmd->exec)
	{
		ft_dprintf(2, "patate: command '%s' not found\n", cmd->args[0]);
		return (clear_proc(shell, cmd, 0), set_rval(127, NULL));
	}
	execve(cmd->exec, cmd->args, shell->env);
	ft_dprintf(2, "patate: command '%s' not found\n", cmd->args[0]);
	return (clear_proc(shell, cmd, 0), set_rval(127, NULL));
}

int	exec_childbis(t_data *shell, t_cmd *cmd)
{
	exec_builtins(shell, cmd, 0);
	cmd->exec = get_cmd(shell, cmd->args[0]);
	if (!cmd->exec)
	{
		ft_dprintf(2, "patate: command '%s' not found\n", cmd->args[0]);
		return (clear_proc(shell, cmd, 0), set_rval(127, NULL));
	}
	execve(cmd->exec, cmd->args, shell->env);
	ft_dprintf(2, "patate: command '%s' not found\n", cmd->args[0]);
	return (clear_proc(shell, cmd, 0), set_rval(127, NULL));
}

int	child_proc(t_data *shell, t_cmd *cmd, int *fd)
{
	pid_t pid;

	if (pipe(cmd->pipe) == -1)
		return (clear_proc(shell, cmd, 1), set_rval(1, ERR_OPIPE));
	pid = fork();
	if (pid == -1)
		return (clear_proc(shell, cmd, 1), set_rval(1, ERR_FORK));
	if (!pid)
	{
		if (cmd->id && !cmd->infile && dup2(fd[0], STDIN_FILENO) == -1)
			printf("dup2 in failed\n");
		if (cmd->infile && dup2(cmd->infile, STDIN_FILENO) == -1)
			printf("dup2 inf faile\n");
		if (cmd->id < shell->prompt.nb_cmds - 1)
			if (dup2(cmd->pipe[1], STDOUT_FILENO) == -1)
				printf("dup2 out failed\n");
		if (cmd->id)
		{
			close(fd[0]);
			close(fd[1]);
		}
		exit(exec_child(shell, cmd));
	}
	if (cmd->id)
	{
		close(fd[0]);
		close(fd[1]);
	}
	waitpid(pid, NULL, 0);
	return (1);
}

int	exec(t_data *shell, t_cmd *cmd, int *fd, unsigned int id_cmd)
{
	pid_t	pid;

	if (pars_redir(cmd))
		return (clear_proc(shell, cmd, 1), 1);
	if (striswspace(cmd->cmd))
		return (clear_proc(shell, cmd, 1), 0);
	if (splitargs(cmd, cmd->cmd))
		return (clear_proc(shell, cmd, 1), 1);
	if(shell->prompt.nb_cmds == 1 && exec_builtins(shell, cmd, 1))
		return (0);
	if (pipe(cmd->pipe) == -1)
		return (clear_proc(shell, cmd, 1), set_rval(1, ERR_OPIPE));
	pid = fork();
	if (pid == -1)
		return (clear_proc(shell, cmd, 1), set_rval(1, ERR_FORK));
	if (!pid)
	{
		if (id_cmd && dup2(fd[0], STDIN_FILENO) == -1)
			printf("dup2 in failed\n");
		if (id_cmd < shell->prompt.nb_cmds - 1)
			if (dup2(cmd->pipe[1], STDOUT_FILENO) == -1)
				printf("dup2 out failed\n");
		if (id_cmd)
		{
			close(fd[0]);
			close(fd[1]);
		}
		exit(exec_child(shell, cmd));
	}
	if (id_cmd)
	{
		close(fd[0]);
		close(fd[1]);
	}
	waitpid(pid, NULL, 0);
	clear_proc(shell, cmd, 1);
	return (0);
}
