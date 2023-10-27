/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitcmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:48:14 by liurne            #+#    #+#             */
/*   Updated: 2023/10/23 18:06:47 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static unsigned int	count_cmd(char *line)
{
	int	res;
	int	quote;
	int	dquote;

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
	if (res > 3333)
		return (0);
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

static int	alloc_cmds(t_data *shell, char *line)
{
	shell->prompt.nb_cmds = count_cmd(line);
	if (!shell->prompt.nb_cmds)
		return (ft_dprintf(2, ERR_PIPE1), 2);
	shell->prompt.cmds = (t_cmd *)ft_calloc(shell->prompt.nb_cmds,
			sizeof(t_cmd));
	if (!shell->prompt.cmds)
		return (ft_dprintf(2, ERR_MALLOC), 1);
	return (0);
}

void	free_cmds(t_data *shell)
{
	unsigned int	i;

	i = 0;
	while (i < shell->prompt.nb_cmds)
	{
		if (shell->prompt.cmds[i].cmd)
			free(shell->prompt.cmds[i].cmd);
		i++;
	}
	free(shell->prompt.cmds);
}

int	splitcmds(t_data *shell, char *line)
{
	unsigned int	i;
	int				j;
	int				tmp;

	tmp = alloc_cmds(shell, line);
	if (tmp)
		return (tmp);
	i = 0;
	j = 0;
	while (i < shell->prompt.nb_cmds && j < (int)ft_strlen(line))
	{
		tmp = find_semicolon(line + j);
		if (tmp == -1)
			shell->prompt.cmds[i].cmd = ft_strndup(line + j,
					ft_strlen(line + j));
		else
			shell->prompt.cmds[i].cmd = ft_strndup(line + j, tmp);
		if (!shell->prompt.cmds[i].cmd)
			return (free_cmds(shell), 1);
		j += tmp + 1;
		i++;
	}
	return (0);
}
