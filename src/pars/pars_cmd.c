/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:25:42 by jcoquard          #+#    #+#             */
/*   Updated: 2023/10/02 15:40:49 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pars_chevron(t_data *line, t_cmd *cmd, unsigned int i)
{
	int		chevron;
	char	*msg;

	while (cmd->cmd[i] == '<')
		chevron++;
	if (chevron > 3)
	{
		ft_dprintf(2, "patate: %s \'",ERR_SYNTAX);
		while(chevron - 3)
		{
			ft_putchar_fd('<', 2);
			chevron--;
		}
		ft_dprintf(2, "\'\n");
	}
	if (chevron == 3)
		ft_dprintf(2, "patate: our shell doesn\'t manage '<<<'\n");
	return (0);
}

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
		while (cmd->cmd[i] == '<')
			chevron++;
		
		i++;
	}
}