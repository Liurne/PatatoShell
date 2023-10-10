/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:50:22 by liurne            #+#    #+#             */
/*   Updated: 2023/10/06 17:56:27 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *get_word(char *str)
{
	int		i;
	int		squote;
	int		dquote;
	char	*word;

	i = -1;
	squote = 0;
	dquote = 0;
	word = NULL;
	while (str[++i] && ((!ft_iswhitespace(str[i]) && str[i] != '<' && str[i]
		!= '>' && str[i] != '|') || dquote || squote))
	{
		if (str[i] == '"' && !squote)
			dquote = -dquote + 1;
		else if (str[i] =='\'' && !dquote)
			squote = -squote + 1;
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
	while (*str + i && ft_iswhitespace(*str + i))
		str++;
	word = get_word(str + i);
	if (c == '<' && i == 1)
	
	if (c == '<' && i == 2)

	if (c == '>' && i == 1)
	
	if (c == '>' && i == 2)

	printf("word :'%s'\n", word);
	free(word);
	return (0);
}
int	pars_redir(t_cmd *cmd)
{
	while(*(cmd->cmd))
	{
		if (*(cmd->cmd) == '<' || *(cmd->cmd) == '>')
			get_redir()
		*(cmd->cmd)++;
	}
	return (0);
}