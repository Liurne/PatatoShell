/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:27:40 by liurne            #+#    #+#             */
/*   Updated: 2023/11/13 16:57:10 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_data *shell, t_cmd *cmd, int pid)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	free_child(shell, cmd, pid);
	if (!buff)
		return (ft_dprintf(2, ERR_LOST), 1);
	printf("%s\n", buff);
	free(buff);
	return (set_rval(0, NULL));
}
