/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:09:12 by edecoste          #+#    #+#             */
/*   Updated: 2023/11/10 14:46:34 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export(t_data *shell, char)
{
	int	i;

	i = -1;
	while (shell->env[++i])
		if (ft_strchr(shell->env[i], '='))
			printf("%s\n", shell->env[i]);
}