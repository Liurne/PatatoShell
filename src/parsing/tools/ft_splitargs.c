/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitargs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:14:12 by liurne            #+#    #+#             */
/*   Updated: 2023/10/19 18:41:56 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	nb_arg(t_cmd *cmd, char *str)
{
	int	squote;
	int	dquote;

	squote = 0;
	dquote = 0;
	while (*str)
	{
		while (*str && ft_iswhitespace(*str))
			str++;
		if (*str)
		{
			cmd->nb_args++;
			while (*str && (!ft_iswhitespace(*str) || squote || dquote))
			{
				manage_quote(*str, &squote, &dquote);
				str++;
			}
		}
	}
}

int	len_arg(char *str)
{
	int	len;
	int	squote;
	int	dquote;

	len = 0;
	squote = 0;
	dquote = 0;
	while (*str && (!ft_iswhitespace(*str) || squote || dquote))
	{
		if (!manage_quote(*str, &squote, &dquote))
			len++;
		str++;
	}
	return (len);
}

void	free_arg(t_data *prompt)
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

int	ft_splitargs(t_cmd *cmd, char *line)
{
	unsigned int	i;
	int				j;
	int				tmp;

	cmd->nb_args = count_cmd(cmd, line);
	cmd->args = (char **)ft_calloc(cmd->nb_args, sizeof(char *));
	if (!cmd->args)
		return (1);
	i = 0;
	j = 0;
	while (i < cmd->nb_args && j < (int)ft_strlen(line))
	{
		tmp = find_semicolon(line + j);
		cmd->args[i] = ft_strndup(line + j, tmp);
		j += tmp + 1;
		i++;
	}
	return (0);
}
