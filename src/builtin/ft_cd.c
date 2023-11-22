/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:30:43 by liurne            #+#    #+#             */
/*   Updated: 2023/11/22 13:22:43 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_udpatevar(t_data *shell, char *old_path)
{
	char	*path;

	add_var(shell, "OLDPWD", old_path);
	path = getcwd(NULL, 0);
	if (!path)
		return (set_rval(1, ERR_MALLOC));
	add_var(shell, "PWD", path);
	free(path);
	return (0);
}

int	ft_cd(t_data *shell, t_cmd *cmd, int pid)
{
	char	*path;
	char	*old_path;

	if (cmd->nb_args > 4)
		return (clear_proc(shell, cmd, pid), set_rval(1, ERR_CD2));
	if (cmd->nb_args == 2)
	{
		path = get_env_var(shell, "HOME");
		if (!path)
			return (clear_proc(shell, cmd, pid), set_rval(1, ERR_CD3));
	}
	else
		path = cmd->args[1];
	old_path = getcwd(NULL, 0);
	if (!old_path)
		set_rval(1, ERR_MALLOC);
	if (chdir(path))
		perror("patate: ft_cd");
	else
		cd_udpatevar(shell, old_path);
	free(old_path);
	return (clear_proc(shell, cmd, pid), 0);
}
