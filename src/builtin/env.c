/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:09:12 by edecoste          #+#    #+#             */
/*   Updated: 2023/11/20 11:25:19 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// verifier que l'envirenement existe
void	ft_env(t_data *shell)
{
	int	i;

	i = -1;
	if (!shell->env)
		return ;
	// should be sorted by ascii order
	while (shell->env[++i])
		if (ft_strchr(shell->env[i], '='))
			printf("declare -x %s\n", shell->env[i]);
}
