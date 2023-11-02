/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:50:22 by liurne            #+#    #+#             */
/*   Updated: 2023/11/02 16:00:35 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



//pour outfile creer les fichier meme ceux qui seront pas utilisé
//verifier si les fichier sont crée si la commande est erroné reponse oui meme si commande innexistante
//commande plante sur les redirection first


static char	*get_word(char *str, int *is_quote)
{
	int		i;
	t_quote	quote;
	char	*word;

	i = -1;
	ft_bzero(&quote, sizeof(t_quote));
	word = NULL;
	while (str[++i] && ((!ft_iswhitespace(get_pos(str[i]))
				&& get_pos(str[i]) != '<' && get_pos(str[i]) != '>'
				&& get_pos(str[i]) != '|') || quote.d || quote.s))
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			manage_quote(get_pos(str[i]), &quote);
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
	if (c == '<' && i == 3)
		return (ft_dprintf(2, "patate: we don't manage this option\n"), 1);
	while (*(str + i) && ft_iswhitespace(*(str + i)))
		str++;
	word = get_word(str + i, &is_quote);
	if (c == '<' && i == 1)
		printf("infile '%s'\n", word);
	if (c == '<' && i == 2)
	{
		heredoc(1, word);
	}
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
