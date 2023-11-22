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
	int		res;
	t_quote	quote;

	ft_bzero(&quote, sizeof(t_quote));
	res = 1;
	while (*line)
	{
		manage_quote(*line, &quote);
		if (*line == '|' && !quote.s && !quote.d)
			res++;
		line++;
	}
	if (res > 3333)
		return (0);
	return (res);
}

static int	find_semicolon(char *line)
{
	t_quote	quote;
	int		i;

	ft_bzero(&quote, sizeof(t_quote));
	i = 0;
	while (line[i])
	{
		manage_quote(line[i], &quote);
		if (line[i] == '|' && !quote.s && !quote.d)
			return (i);
		i++;
	}
	return (-1);
}

static int	alloc_cmds(t_data *shell, char *line)
{
	shell->prompt.nb_cmds = count_cmd(line);
	if (!shell->prompt.nb_cmds)
		return (set_rval(2, ERR_PIPE));
	shell->prompt.cmds = (t_cmd *)ft_calloc(shell->prompt.nb_cmds,
			sizeof(t_cmd));
	if (!shell->prompt.cmds)
		return (set_rval(1, ERR_MALLOC));
	return (0);
}

void	free_cmds(t_data *shell)
{
	unsigned int	i;

	i = 0;
	while (i < shell->prompt.nb_cmds)
	{
		if (shell->prompt.cmds[i].cmd)
		{
			close_child(&(shell->prompt.cmds[i]));
			free(shell->prompt.cmds[i].cmd);
		}
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
		shell->prompt.cmds[i].id = i;
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
