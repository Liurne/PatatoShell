/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:27:40 by liurne            #+#    #+#             */
/*   Updated: 2023/11/24 17:52:49 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_data *shell, int pid)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	clear_proc(shell, pid);
	if (!buff)
		return (ft_dprintf(2, ERR_LOST), 1);
	printf("%s\n", buff);
	free(buff);
	return (set_rval(0, NULL));
}
