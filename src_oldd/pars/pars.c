/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:06:21 by jcoquard          #+#    #+#             */
/*   Updated: 2023/10/05 17:12:27 by liurne           ###   ########.fr       */
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
			line->line.cmds->redir = 1;
			if (is_redir(cmd, cmd->cmd + i, cmd->cmd[i]))
				return;
			printf("command then:'%s'\n", cmd->cmd);
		}
		i++;
	}
}

int	pars(t_data *prompt)
{
	unsigned int	i;
	if (ft_striswhitespace(prompt->line.line))
		return (0);
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
	free_cmd(prompt);
	return (0);
}
