/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:09:12 by edecoste          #+#    #+#             */
/*   Updated: 2023/12/01 13:07:44 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*pars_var(char *arg)
{
	char	*word;

	word = NULL;
	if (!ft_isalpha(*arg) && *arg != '_')
	{
		ft_dprintf(2, "patate: export: '%s': not a valid identifier\n", arg);
		return (set_rval(1, NULL), NULL);
	}
	while (*arg && *arg != '=')
	{
		if (!ft_isalnum(*arg) && *arg != '_')
		{
			ft_dprintf(2, "patate: export: '%s': not a valid identifier\n",
				arg);
			if (word)
				free(word);
			return (set_rval(1, NULL), NULL);
		}
		word = ft_addchar(word, *arg);
		if (!word)
			return (set_rval(1, ERR_MALLOC), NULL);
		arg++;
	}
	return (word);
}

int	ft_export(t_data *shell, t_cmd *cmd, int pid)
{
	int		i;
	char	*var;

	var = NULL;
	if (cmd->nb_args == 2)
		put_sortedstr(shell->env, 0, len_env(shell->env) - 1);
	else
	{
		i = 0;
		while (++i < cmd->nb_args - 1)
		{
			var = pars_var(cmd->args[i]);
			if (var && cmd->args[i][ft_strlen(var)])
				add_var(shell, var, cmd->args[i] + ft_strlen(var));
			else if (var)
				add_var(shell, var, NULL);
			if (var)
				free(var);
		}
	}
	clear_proc(shell, pid);
	return (set_rval(0, NULL));
}
