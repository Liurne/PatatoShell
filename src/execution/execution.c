/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:54:21 by liurne            #+#    #+#             */
/*   Updated: 2023/11/29 19:23:48 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//penser au fait que ctrl \ doit quitter les cat sans outfile!!
//si cmd not found verif valeur de retour
//verifier mon syteme de quote
//heredoc ce lance pas forcement
//signaux douteux dans le heredoc
//bien close les fd 
//lancer toutes les execs puis les waitpid une fois tout exec

void	close_cmd(t_cmd *cmd)
{
	if (cmd->infile)
	{
		//ft_dprintf(2, "in:%d closed\n", cmd->infile);
		ft_close(&(cmd->infile));
	}
	if (cmd->outfile)
	{
		//ft_dprintf(2, "out:%d closed\n", cmd->outfile);
		ft_close(&(cmd->outfile));
	}
	if (cmd->pipe[1])
	{
		//ft_dprintf(2, "pipe 1:%d closed\n", cmd->pipe[1]);
		ft_close(&(cmd->pipe[1]));
	}
	if (cmd->pipe[0])
	{
		//ft_dprintf(2, "pipe 0:%d closed\n", cmd->pipe[0]);
		ft_close(&(cmd->pipe[0]));
	}
}

static int	wait_childs(t_data *shell, t_cmd *cmds)
{
	int				rval;
	unsigned int	i;

	rval = 0;
	i = -1;
	while (++i < shell->prompt.nb_cmds)
	{
		if (waitpid(cmds[i].pid, &rval, WUNTRACED) == -1)
			set_rval(1, NULL);
		else if (WIFEXITED(rval))
			set_rval(WEXITSTATUS(rval), NULL);
	}
	return (g_rvalue);
}

static int	child_exec(t_data *shell, t_cmd *cmd)
{
	exec_signals();
	exec_builtins(shell, cmd, 0);
	if (cmd->args[0][0] == '.' || cmd->args[0][0] == '/')
	{
		if (!access((cmd->args[0]), X_OK))
			execve(cmd->args[0], cmd->args, shell->env);
		else
		{
			ft_dprintf(2, "patate: no such file or directory: '%s'\n",
				cmd->args[0]);
			return (clear_proc(shell, 0), set_rval(127, NULL));
		}
		ft_dprintf(2, "patate: no such file or directory: '%s'\n",
			cmd->args[0]);
		return (clear_proc(shell, 0), set_rval(127, NULL));
	}
	cmd->exec = get_cmd(shell, cmd->args[0]);
	if (!cmd->exec)
	{
		ft_dprintf(2, "patate: command '%s' not found\n", cmd->args[0]);
		return (clear_proc(shell, 0), set_rval(127, NULL));
	}
	execve(cmd->exec, cmd->args, shell->env);
	ft_dprintf(2, "patate: command '%s' not found\n", cmd->args[0]);
	return (clear_proc(shell, 0), set_rval(127, NULL));
}

int	child_proc(t_data *shell, t_cmd *cmd)
{
	if (cmd->id + 1 < shell->prompt.nb_cmds && pipe(cmd->pipe) == -1)
		return (close_cmd(cmd), set_rval(1, ERR_OPIPE));
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (close_cmd(cmd), set_rval(1, ERR_FORK));
	if (!cmd->pid)
	{
		if (cmd->infile && dup2(cmd->infile, STDIN_FILENO) == -1)
			printf("dup2 in failed\n");
		if (cmd->outfile && dup2(cmd->outfile, STDOUT_FILENO) == -1)
			printf("dup2 out failed\n");
		else if (cmd->id < shell->prompt.nb_cmds - 1
			&& dup2(cmd->pipe[1], STDOUT_FILENO) == -1)
			printf("dup2 out failed\n");
		close_cmd(cmd);
		exit(child_exec(shell, cmd));
	}
	if (cmd->id + 1 < shell->prompt.nb_cmds
		&& !shell->prompt.cmds[cmd->id + 1].infile)
	{
		shell->prompt.cmds[cmd->id + 1].infile = cmd->pipe[0];
		cmd->pipe[0] = 0;
	}
	return (close_cmd(cmd), g_rvalue);
}

int	exec(t_data *shell, t_cmd *cmds)
{
	unsigned int	i;

	i = -1;
	unplug_signals();
	//set_rval(0, NULL);
	while (++i < shell->prompt.nb_cmds)
	{
		if (pars_redir(&(cmds[i])))
			return (1);
		if (striswspace(cmds[i].cmd))
			return (0);
		if (splitargs(&(cmds[i]), cmds[i].cmd))
			return (1);
		if (shell->prompt.nb_cmds == 1)
			if (exec_builtins(shell, &(cmds[i]), 1))
				return (g_rvalue);
		child_proc(shell, &(cmds[i]));
	}
	return(wait_childs(shell, cmds));
}
