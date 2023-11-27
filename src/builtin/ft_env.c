/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:09:12 by edecoste          #+#    #+#             */
/*   Updated: 2023/11/24 17:54:16 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_data *shell, int pid)
{
	int	i;

	i = -1;
	while (shell->env && shell->env[++i])
		if (ft_strchr(shell->env[i], '='))
			printf("%s\n", shell->env[i]);
	clear_proc(shell, pid);
	set_rval(0, NULL);
}
