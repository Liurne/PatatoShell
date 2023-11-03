/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:56:04 by liurne            #+#    #+#             */
/*   Updated: 2023/11/03 15:41:14 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**get_path(t_data *shell)
{
	char	**res;

	if (!get_env_var(shell, "PATH"))
		return (ft_dprintf(2, "patate: path unset\n"), NULL);
	res = ft_split(get_env_var(shell, "PATH"), ':');
	if (!res)
		return (ft_dprintf(2, ERR_MALLOC), NULL);
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
			return (ft_dprintf(2, ERR_MALLOC), free_dtab(paths), NULL);
		res = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!res)
			return (ft_dprintf(2, ERR_MALLOC), free_dtab(paths), NULL);
		if (access(res, X_OK) == 0)
			return (free_dtab(paths), res);
		free(res);
		i++;
	}
	return (free_dtab(paths), NULL);
}
