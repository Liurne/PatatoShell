/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:14:53 by liurne            #+#    #+#             */
/*   Updated: 2023/11/29 19:10:23 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	echo_option(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] == '-')
	{
		while (arg[i] && arg[i] == 'n')
			i++;
		if (!arg[i] && i > 1)
			return (1);
	}
	return (0);
}

char	*echo_join(char **args, int endl)
{
	char	*tmp;
	char	*res;
	int		i;

	i = 2 - endl;
	tmp = NULL;
	while (args[i])
	{
		res = ft_strjoin(tmp, args[i]);
		if (tmp)
			free(tmp);
		if (!res && args[i][0])
			return (set_rval(1, ERR_MALLOC), NULL);
		if (args[i + 1])
		{
			tmp = ft_strjoin(res, " ");
			free (res);
			if (!tmp)
				return (set_rval(1, ERR_MALLOC), NULL);
		}
		i++;
	}
	return (res);
}

int	ft_echo(t_data *shell, t_cmd *cmd, int pid)
{
	int		endl;
	char	*str;

	if (!cmd->args[1])
		return (ft_dprintf(2, "\n"), clear_proc(shell, pid),
			set_rval(0, NULL));
	endl = 1 - echo_option(cmd->args[1]);
	if (!endl && !cmd->args[2])
		return (clear_proc(shell, pid), set_rval(0, NULL));
	str = echo_join(cmd->args, endl);
	clear_proc(shell, pid);
	if (g_rvalue)
		return (g_rvalue);
	if (!str && !endl)
		return (set_rval(0, NULL));
	if (!str)
		return (printf("\n"), set_rval(0, NULL));
	if (endl)
		return (printf("%s\n", str), free(str), set_rval(0, NULL));
	return (printf("%s", str), free(str), set_rval(0, NULL));
}
