/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:05:04 by liurne            #+#    #+#             */
/*   Updated: 2023/11/08 15:40:54 by liurne           ###   ########.fr       */
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
		return (free_child(shell, cmd, 0), set_rval(127, NULL));
	}
	execve(cmd->exec, cmd->args, shell->env);
	ft_dprintf(2, "patate: command '%s' not found\n", cmd->args[0]);
	
	return (free_child(shell, cmd, 0), set_rval(127, NULL));
}

char	*read_file(int fd)
{
	char	buff[43];
	int		rbytes;
	char	*str;

	rbytes = 1;
	str = NULL;
	while (rbytes == 42)
	{
		rbytes = read(fd, buff, 42);
		if (rbytes == -1)
		{
			if (str)
				free(str);
			str = NULL;
			break;
		}
		buff[rbytes] = '\0';
		str = ft_strjoin(str, buff);
	}
	printf("prout\n");
	return (str);
}

int exec_tmp(t_data*shell, t_cmd *cmd)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return (printf("fail pipe\n"), 1);
	dprintf(2, "dar : pipef in: %d, pipefd out: %d\n",fd[1] ,fd[0]);
	pid = fork();
	if (pid == -1)
		return (printf("fail fork\n"), 1);
	if (!pid)
	{
		free_child(shell, cmd, 0);
		dprintf(2, "gosse : pipef in: %d, pipefd out: %d\n",fd[1] ,fd[0]);
		int zub = dprintf(fd[1], "bichour\n");
		dprintf(2, "zub value:%d\n", zub);
		close(fd[0]);
		close(fd[1]);
		exit(111);
	}
	else if (pid > 0)
	{
		char	*str;
		dprintf(2, "dar again: pipef in: %d, pipefd out: %d\n",fd[1] ,fd[0]);
		str = NULL;
		free_child(shell, cmd, 1);
		//if(dup2(fd[0], STDIN_FILENO) == -1)
		//	printf("fail dup2 main");
		printf("merde\n");
		int i = read(fd[0], str, 2048);
		ft_dprintf(2, "read ret val: %d\n", i);
		if (str)
			ft_dprintf(2, "read red: %s\n", str);
		else
			ft_dprintf(2, "read don't red\n");
	}
	int stat;

	stat = 0;
	waitpid(pid, &stat, 0);
	ft_dprintf(2, "child exit status: %d",WEXITSTATUS(stat));
	//close(fd[0]);
	//close(fd[1]);
	return (0);
}

int	exec(t_data *shell, t_cmd *cmd, unsigned int id_cmd)
{
	pid_t	pid;
	int		fd[2];

	if (pars_redir(cmd))
		return (free_child(shell, cmd, 1), 1);
	if (striswspace(cmd->cmd))
		return (free_child(shell, cmd, 1), 0);
	if (splitargs(cmd, cmd->cmd))
		return (free_child(shell, cmd, 1), 1);
//	if(shell->prompt.nb_cmds == 1)
	if (id_cmd < shell->prompt.nb_cmds - 1 && pipe(fd) == -1)
		return (free_child(shell, cmd, 1), set_rval(1, ERR_OPIPE));
	pid = fork();
	if (pid == -1)
		return (free_child(shell, cmd, 1), set_rval(1, ERR_FORK));
	if (!pid)
	{
		if (id_cmd < shell->prompt.nb_cmds - 1)
		{
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				printf("TNUL\n");
			close(fd[0]);
		}
		exit(exec_child(shell, cmd));
	}
	else
	{
		printf("id cmd : %d and nb cmd : %d\n", id_cmd, shell->prompt.nb_cmds - 1);
		if (!id_cmd)
		{
			if(dup2(fd[0], STDIN_FILENO) == -1)
				printf("TCON\n");
			close(fd[0]);
			close(fd[1]);
			if (!STDIN_FILENO)
				printf("YOUP\n");
		}
	}
	free_child(shell, cmd, 1);
	if (!STDIN_FILENO)
	{
		printf("TCOOOOON\n");
	}
	return (0);
}
