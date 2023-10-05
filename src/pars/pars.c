/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:06:21 by jcoquard          #+#    #+#             */
/*   Updated: 2023/10/04 18:27:59 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//parcours de la commande pour heredocs
//si heredocs regarder si delimiteur et si quote
//regarder redirection (peut avoir autant de redirection au'on veut mais seul la derniere importe)
//regarder si quote et traiter texte entre quote
//garder que les element de la commande
//exec la/les commande/s

void	pars_cmd(t_data *line, t_cmd *cmd)
{
	unsigned int	i;

	i = 0;
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i] == '<' || cmd->cmd[i] == '>')
		{
			is_redir(&line->line.cmds[0], line->line.cmds[0].cmd + i, cmd->cmd[i]);
			return;
		}
			
		i++;
	}
}

int	pars(t_data *prompt)
{
	unsigned int	i;

	if (ft_split_cmd(prompt, prompt->line.line))
		ft_dprintf(2, "error split\n");
	i = 0;
	while (i < prompt->line.nb_cmds)
	{
		if (prompt->line.cmds[i].cmd)
			printf("%s\n", prompt->line.cmds[i].cmd);
		else
			printf("\n");
		i++;
	}
	pars_cmd(prompt, &prompt->line.cmds[0]);
	return (0);
}
