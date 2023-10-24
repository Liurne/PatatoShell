/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:50:22 by liurne            #+#    #+#             */
/*   Updated: 2023/10/19 18:35:36 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_word(char *str)
{
	int		i;
	t_quote	quote;
	char	*word;

	i = -1;
	ft_bzero(&quote, sizeof(t_quote));
	word = NULL;
	while (str[++i] && ((!ft_iswhitespace(str[i]) && str[i] != '<' && str[i]
				!= '>' && str[i] != '|') || quote.d || quote.s))
	{
		if (str[i] == '"' || str[i] == '\'')
			manage_quote(str[i], &quote);
		else
		{
			word = ft_addchar(word, str[i]);
			if (!word)
				return (NULL);
		}
		str[i] = ' ';
	}
	return (word);
}

static int	get_redir(t_cmd *cmd, char *str, char c)
{
	int		i;
	char	*word;

	(void)cmd;
	i = -1;
	while (str[++i] == c)
		str[i] = ' ';
	if (c == '<' && i == 3)
		return (ft_dprintf(2, "patate: we don't manage this option\n"), 1);
	while (*(str + i) && ft_iswhitespace(*(str + i)))
		str++;
	word = get_word(str + i);
	if (c == '<' && i == 1)
		printf("infile '%s'\n", word);
	if (c == '<' && i == 2)
		printf("heredoc delimiter:'%s'\n", word);
	if (c == '>' && i == 1)
		printf("outfile '%s'\n", word);
	if (c == '>' && i == 2)
		printf("outfile append '%s'\n", word);
	free(word);
	return (0);
}

int	pars_redir(t_cmd *cmd)
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
