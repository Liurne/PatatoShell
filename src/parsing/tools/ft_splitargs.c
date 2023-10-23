/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitargs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:14:12 by liurne            #+#    #+#             */
/*   Updated: 2023/10/23 18:24:03 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	count_arg(char *line)
{
	int		res;
	t_quote	quote;
	
	res = 1;
	ft_bzero(&quote, sizeof(t_quote));
	while (*line)
	{
		if (ft_iswhitespace(*line) && !quote.s && !quote.d)
		{
			while(*line && ft_iswhitespace(*line))
				line++;
			if(!*line)
				return (res);
			if (*line)
				res++;
		}
		line++;
	}
	return (res);
}

static int alloc_arg(t_cmd *cmd, char *line, int arg)
{
	int		len;
	t_quote	quote;

	len = 0;
	ft_bzero(&quote, sizeof(t_quote));
	while (line[len] && (!ft_iswhitespace(line[len]) || quote.s || quote.d))
	{
		if (manage_quote(line[len], &quote))
		{
			line++;
			len--;
		}
		len++;
	}
	cmd->args[arg] = ft_calloc(len + 1, sizeof(char));
	if (!cmd->args[arg])
		return (ft_dprintf(2, ERR_MALLOC), free_dtab(cmd->args), 1);
	return (0);
}

int	split_cpy(char *line, char *arg)
{
	t_quote	quote;
	int		tmp;
	int		i;

	ft_bzero(&quote, sizeof(t_quote));
	i = 0;
	tmp = 0;
	while (line[tmp] && (!ft_iswhitespace(line[tmp]) || quote.s || quote.d))
	{
		if(!manage_quote(line[tmp], &quote))
		{
			arg[i] = line[tmp];
			i++;
		}
		tmp++;
	}
	return (tmp);
}
int	ft_splitargs(t_cmd *cmd, char *line)
{
	int		i;

	cmd->nb_args = count_arg(line) + 1;
	cmd->args = ft_calloc(cmd->nb_args, sizeof(char *));
	if (!cmd->args)
		return (ft_dprintf(2, ERR_MALLOC), 1);
	i = 0;
	while (i < cmd->nb_args && *line)
	{
		if (alloc_arg(cmd, line, i))
			return (1);
		line += split_cpy(line, cmd->args[i]);
		while (*line && ft_iswhitespace(*line))
			line++;
		i++;
	}
	return (0);
}
