/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:59:29 by jcoquard          #+#    #+#             */
/*   Updated: 2023/10/30 18:10:07 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_heredocs(t_cmd *cmd, char *str, char c)
{
	int		i;
	char	*word;
	int		is_quote;

	(void)cmd;
	is_quote = 0;
	i = -1;
	while (str[++i] == c)
		str[i] = ' ';
	while (*(str + i) && ft_iswhitespace(get_pos(*(str + i))))
		str++;
	if (c == '<' && i == 2)
	{
		word = get_word(str + i, &is_quote);
		if (!word)
			return (2);
		//exec heredoc
		free(word);
	}
	return (0);
}

int pars_heredoc(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i] == '<' || cmd->cmd[i] == '>')
			get_redir(cmd, cmd->cmd + i, *(cmd->cmd + i));
		i++;
	}
	return (0);
}