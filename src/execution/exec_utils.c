/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:56:04 by liurne            #+#    #+#             */
/*   Updated: 2023/11/16 17:22:56 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	else if (!ft_strcmp(cmd->args[0], "echo"))
		ft_echo(shell, cmd, pid);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		ft_pwd(shell, cmd, pid);
	else
		return (0);
	if (!pid)
		exit(g_rvalue);
	return (1);
}
