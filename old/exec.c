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
	if (pipe(fd) == -1)
		return (free_child(shell, cmd, 1), set_rval(1, ERR_OPIPE));
	pid = fork();
	if (pid == -1)
		return (free_child(shell, cmd, 1), set_rval(1, ERR_FORK));
	if (!pid)
	{
		if (id_cmd < shell->prompt.nb_cmds - 1)
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				printf("dup2 out failed\n");
		close(fd[0]);
		close(fd[1]);
		exit(exec_child(shell, cmd));
	}
	else if (pid > 0)
		if(dup2(fd[0], STDIN_FILENO) == -1)
			printf("dup2 in failed\n");
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	free_child(shell, cmd, 1);
	return (0);
}