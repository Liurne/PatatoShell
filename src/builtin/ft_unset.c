/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:31:00 by liurne            #+#    #+#             */
/*   Updated: 2023/12/06 16:00:35 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pars_unset(char *arg)
{
	if (arg && !ft_isalpha(*arg) && *arg != '_')
	{
		ft_dprintf(2, "patate: unset: '%s': not a valid identifier\n", arg);
		return (set_rval(1, NULL));
	}
	while (arg && *arg)
	{
		if (!ft_isalnum(*arg) && *arg != '_')
		{
			ft_dprintf(2, "patate: unset: '%s': not a valid identifier\n",
				arg);
			return (set_rval(1, NULL));
		}
		arg++;
	}
	return (0);
}

int	ft_unset(t_data *shell, t_cmd *cmd, int pid)
{
	int	i;

	i = 1;
	set_rval(0, NULL);
	while (i < cmd->nb_args - 1)
	{
		if (!pars_unset(cmd->args[i]) && is_var(shell->env, cmd->args[i]))
			if (del_var(shell, cmd->args[i]))
				return (1);
		i++;
	}
	clear_proc(shell, pid);
	if (!pid)
		exit(g_rvalue);
	return (set_rval(0, NULL));
}
