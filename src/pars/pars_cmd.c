/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:25:42 by jcoquard          #+#    #+#             */
/*   Updated: 2023/10/03 14:24:00 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

	//diviser les args et si >> couper + mots en 1case !!

int	pars_cmd(t_data *line, t_cmd *cmd)
{
	unsigned int	i;
	int				squote;
	int				dquote;

	i = 0;
	while (cmd->cmd[i])
	{
		while (ft_iswhitespace(cmd->cmd[i]))
			i++;
		while (cmd->cmd[i] == '<' || cmd->cmd[i] == '>')
			chevron++;
		
		i++;
	}
}