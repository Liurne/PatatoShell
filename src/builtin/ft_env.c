/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:09:12 by edecoste          #+#    #+#             */
/*   Updated: 2023/11/17 16:47:08 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_data *shell, t_cmd *cmd, int pid)
{
	int	i;

	i = -1;
	while (shell->env[++i])
		if (ft_strchr(shell->env[i], '='))
			printf("%s\n", shell->env[i]);
	return (set_rval(0, NULL);)
}
