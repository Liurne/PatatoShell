/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:56:04 by liurne            #+#    #+#             */
/*   Updated: 2023/12/04 15:34:22 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_heredoc(pid_t pid)
{
	if (waitpid(pid, &g_rvalue, WUNTRACED) == -1)
		set_rval(1, NULL);
	else if (WIFEXITED(g_rvalue))
		set_rval(WEXITSTATUS(g_rvalue), NULL);
	else if (WIFSIGNALED(g_rvalue))
		exec_handler(WTERMSIG(g_rvalue));
}

void	ft_close(int *fd)
{
	if (*fd)
	{
		close(*fd);
		*fd = 0;
	}
}

static char	**get_path(t_data *shell)
{
	char	**res;

	if (!get_env_var(shell, "PATH"))
		return (NULL);
	res = ft_split(get_env_var(shell, "PATH"), ':');
	if (!res)
		return (set_rval(1, ERR_MALLOC), NULL);
	return (res);
}

char	*get_cmd(t_data *shell, char *cmd)
{
	char	*tmp;
	char	*res;
	char	**paths;
	int		i;

	paths = get_path(shell);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (set_rval(1, ERR_MALLOC), free_dtab(paths), NULL);
		res = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!res)
			return (set_rval(1, ERR_MALLOC), free_dtab(paths), NULL);
		if (access(res, X_OK) == 0)
			return (free_dtab(paths), res);
		free(res);
		i++;
	}
	return (free_dtab(paths), NULL);
}

int	exec_builtins(t_data *shell, t_cmd *cmd, int pid)
{
	if (!ft_strcmp(cmd->args[0], "exit"))
		ft_exit(shell, cmd, cmd->args, pid);
	else if (!ft_strcmp(cmd->args[0], "echo") && !pid)
		ft_echo(shell, cmd, pid);
	else if (!ft_strcmp(cmd->args[0], "pwd") && !pid)
		ft_pwd(shell, pid);
	else if (!ft_strcmp(cmd->args[0], "env") && !pid)
		ft_env(shell, pid);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		ft_unset(shell, cmd, pid);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		ft_cd(shell, cmd, pid);
	else if (!ft_strcmp(cmd->args[0], "export"))
	{
		if (pid && cmd->nb_args == 2)
			return (0);
		else
			ft_export(shell, cmd, pid);
	}
	else
		return (0);
	if (!pid)
		exit(g_rvalue);
	return (1);
}
