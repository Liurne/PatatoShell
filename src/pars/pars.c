/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:06:21 by jcoquard          #+#    #+#             */
/*   Updated: 2023/09/06 01:27:12 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pars(t_data *prompt)
{
	unsigned int	i;
	if (ft_split_cmd(prompt, prompt->line.line))
		printf("error split\n");
	i = 0;
	while (i < prompt->line.nb_cmds)
	{
		if (prompt->line.cmds[i].cmd)
			printf("%s\n", prompt->line.cmds[i].cmd);
		else
			printf("\n");
		i++;
	}
	return(0);
}