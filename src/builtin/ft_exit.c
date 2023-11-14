/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:41:12 by edecoste          #+#    #+#             */
/*   Updated: 2023/11/13 16:58:44 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valide_number(char *str)
{
	long long	temp;
	int			nb_len;

	temp = ft_atoll(str);
	nb_len = 0;
	while ((str[nb_len] && (str[nb_len] > 8 && str[nb_len] < 14)) || str[nb_len] == ' ')
		nb_len++;
	nb_len = ft_strlen(str) - nb_len;
	if ((temp == 0 || temp == -1) && nb_len > 1)
		return (EXIT_FAILURE);
	if (!ft_strcmp(str, "0") || temp != 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	is_valide_argv(char *arg, int argc)
{
	if (argc == 1)
	{
		g_rvalue = 0;
		ft_dprintf(1, "exit\n");
		return (1);
	}
	else if (!valide_number(arg) && argc > 2)
	{
//		ft_dprintf(2, "exit\n%sexit: too many arguments", PRONPT);
		return (0);
	}
	else if (!valide_number(arg) && argc == 2)
	{
		g_rvalue = ft_atoll(arg) % 256;
		ft_dprintf(1, "exit\n");
		return (1);
	}
	g_rvalue = 2;
//	printf("exit\n%sexit: %s: numeric argument required\n", PRONPT, arg);
	return (2);
}

int	ft_exit(t_data *shell, t_cmd *cmd, char **arg, int pid)
{
	int		argc;
	int		return_type;

	argc = 0;
	while (arg[argc])
		argc++;
	return_type = is_valide_argv(arg[1], argc);
	if (return_type == 1 || return_type == 2)
	{
		free_child(shell, cmd, 0);
		exit(g_rvalue);
	}
	return (free_child(shell, cmd, pid), set_rval(1, NULL));
}