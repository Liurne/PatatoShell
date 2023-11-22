/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:54:21 by liurne            #+#    #+#             */
/*   Updated: 2023/11/22 15:20:40 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//penser au fait que ctrl \ doit quitter les cat sans outfile!!
//si cmd not found verif valeur de retour
//verifier mon syteme de quote
//heredoc ce lance pas forcement
//signaux douteux dans le heredoc

void	close_child(t_cmd *cmd)
{
	if (cmd->infile)
		close(cmd->infile);
	if (cmd->outfile)
		close(cmd->outfile);
	if (cmd->pipe[1])
		close(cmd->pipe[1]);
	if (cmd->pipe[0])
		close(cmd->pipe[0]);
}

static int	child_exec(t_data *shell, t_cmd *cmd)
{
	exec_builtins(shell, cmd, 0);
	if (cmd->args[0][0] == '.' || cmd->args[0][0] == '/')
	{
		if (!access((cmd->args[0]), X_OK))
			execve(cmd->args[0], cmd->args, shell->env);
		else
		{
			ft_dprintf(2, "patate: no such file or directory: '%s'\n",
				cmd->args[0]);
			return (clear_proc(shell, cmd, 0), set_rval(127, NULL));
		}
		ft_dprintf(2, "patate: no such file or directory: '%s'\n",
			cmd->args[0]);
		return (clear_proc(shell, cmd, 0), set_rval(127, NULL));
	}
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

static int	wait_child(pid_t pid)
{
	int	rval;

	rval = 0;
	if (waitpid(pid, &rval, WUNTRACED) == -1)
		return (set_rval(1, NULL));
	else if (WIFEXITED(rval))
		set_rval(WEXITSTATUS(rval), NULL);
	return (g_rvalue);
}

static int	child_proc(t_data *shell, t_cmd *cmd)
{
	pid_t	pid;

	if (cmd->id + 1 < shell->prompt.nb_cmds && pipe(cmd->pipe) == -1)
		return (clear_proc(shell, cmd, 1), set_rval(1, ERR_OPIPE));
	pid = fork();
	if (pid == -1)
		return (clear_proc(shell, cmd, 1), set_rval(1, ERR_FORK));
	if (!pid)
	{
		if (cmd->infile && dup2(cmd->infile, STDIN_FILENO) == -1)
			printf("dup2 in failed\n");
		if (cmd->outfile && dup2(cmd->outfile, STDOUT_FILENO) == -1)
			printf("dup2 out failed\n");
		else if (cmd->id < shell->prompt.nb_cmds - 1
			&& dup2(cmd->pipe[1], STDOUT_FILENO) == -1)
			printf("dup2 out failed\n");
		close_child(cmd);
		exit(child_exec(shell, cmd));
	}
	if (cmd->id + 1 < shell->prompt.nb_cmds
		&& !shell->prompt.cmds[cmd->id + 1].infile)
		shell->prompt.cmds[cmd->id + 1].infile = cmd->pipe[0];
	return (wait_child(pid));
}

int	exec(t_data *shell, t_cmd *cmd)
{
	set_rval(0, NULL);
	if (pars_redir(cmd))
		return (clear_proc(shell, cmd, 1), 1);
	if (striswspace(cmd->cmd))
		return (clear_proc(shell, cmd, 1), 0);
	if (splitargs(cmd, cmd->cmd))
		return (clear_proc(shell, cmd, 1), 1);
	if (shell->prompt.nb_cmds == 1)
		if (exec_builtins(shell, cmd, 1))
			return (g_rvalue);
	if (cmd->redir_in == HEREDOC)
		cmd->infile = cmd->pipe[0];
	child_proc(shell, cmd);
	clear_proc(shell, cmd, 1);
	return (0);
}
