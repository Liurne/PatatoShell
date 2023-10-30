/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:35:15 by jcoquard          #+#    #+#             */
/*   Updated: 2023/10/30 18:10:57 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_word(char *str, int *is_quote)
{
	int		i;
	t_quote	quote;
	char	*word;

	i = -1;
	ft_bzero(&quote, sizeof(t_quote));
	word = NULL;
	while (str[++i] && ((!ft_iswhitespace(get_pos(str[i]))
				&& str[i] != '<' && str[i] != '>'
				&& str[i] != '|') || quote.d || quote.s))
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			manage_quote(str[i], &quote);
			*is_quote = 1;
		}
		else
		{
			word = ft_addchar(word, get_pos(str[i]));
			if (!word)
				return (NULL);
		}
		str[i] = ' ';
	}
	return (word);
}

int	set_redir(t_cmd *cmd, char *word, int redir);

static int	get_redir(t_cmd *cmd, char *str, char c)
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
	word = get_word(str + i, &is_quote);
	if (c == '<' && i == 1)
		printf("infile '%s'\n", word);
	if (c == '<' && i == 2)
		printf("heredoc delimiter:'%s' is quote ?:%d\n", word, is_quote);
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