/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 00:47:02 by liurne            #+#    #+#             */
/*   Updated: 2023/10/03 14:11:10 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static unsigned int	count_cmd(char *line)
{
	unsigned int	res;
	int				quote;
	int				dquote;

	res = 1;
	quote = 0;
	dquote = 0;
	while (*line)
	{
		if (*line == '\'' && !dquote)
			quote = -quote + 1;
		if (*line == '"' && !quote)
			dquote = -dquote + 1;
		if (*line == '|' && !quote && !dquote)
			res++;
		line++;
	}
	return (res);
}

static int	find_semicolon(char *line)
{
	int	quote;
	int	dquote;
	int	i;

	quote = 0;
	dquote = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !dquote)
			quote = -quote + 1;
		if (line[i] == '"' && !quote)
			dquote = -dquote + 1;
		if (line[i] == '|' && !quote && !dquote)
			return (i);
		i++;
	}
	return (-1);
}

void	free_cmd(t_data *prompt)
{
	unsigned int	i;

	i = 0;
	while (i < prompt->line.nb_cmds)
	{
		if (prompt->line.cmds[i].cmd)
			free(prompt->line.cmds[i].cmd);
		i++;
	}
	free(prompt->line.cmds);
}

int	ft_split_cmd(t_data *prompt, char *line)
{
	unsigned int	i;
	int				j;
	int				tmp;

	prompt->line.nb_cmds = count_cmd(line);
	prompt->line.cmds = (t_cmd *)ft_calloc(prompt->line.nb_cmds, sizeof(t_cmd));
	if (!prompt->line.cmds)
		return (1);
	i = 0;
	j = 0;
	while (i < prompt->line.nb_cmds && j < (int)ft_strlen(line))
	{
		tmp = find_semicolon(line + j);
		if (tmp == -1)
			prompt->line.cmds[i].cmd = ft_strndup(line + j,
					ft_strlen(line + j));
		else
			prompt->line.cmds[i].cmd = ft_strndup(line + j, tmp);
		j += tmp + 1;
		i++;
	}
	return (0);
}
