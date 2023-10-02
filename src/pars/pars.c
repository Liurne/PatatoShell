/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:06:21 by jcoquard          #+#    #+#             */
/*   Updated: 2023/10/02 15:04:00 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//parcours de la commande pour heredocs
//si heredocs regarder si delimiteur et si quote
//regarder redirection (peut avoir autant de redirection au'on veut mais seul la derniere importe)
//regarder si quote et traiter texte entre quote
//garder que les element de la commande
//exec la/les commande/s

int	pars_cmd(t_data *line, t_cmd *cmd)
{
	unsigned int	i;
	int				squote;
	int				dquote;
	int				chevron;

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
	return (0);
}
