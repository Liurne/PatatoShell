/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:27:40 by liurne            #+#    #+#             */
/*   Updated: 2023/12/04 13:02:23 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_data *shell, int pid)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	clear_proc(shell, pid);
	if (!buff)
		return (set_rval(2, ERR_LOST), 1);
	printf("%s\n", buff);
	free(buff);
	return (set_rval(0, NULL));
}
