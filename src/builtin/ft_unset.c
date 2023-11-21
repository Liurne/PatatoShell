/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:31:00 by liurne            #+#    #+#             */
/*   Updated: 2023/11/21 16:55:21 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_data *shell, t_cmd *cmd, int pid)
{
	int	i;

	i = 1;
	while (i < cmd->nb_args)
	{
		if (is_var(shell->env, cmd->args[i]))
			if (del_var(shell, cmd->args[i]))
				return (1);
		i++;
	}
	clear_proc(shell, cmd, pid);
	if (!pid)
		exit(g_rvalue);
	return (g_rvalue);
}
