/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:12:00 by liurne            #+#    #+#             */
/*   Updated: 2023/10/05 17:19:06 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_syntax_too_much(int nb_c, char c)
{
	ft_dprintf(2, "patate: syntax error near unexpected token '");
	while (nb_c--)
		ft_putchar_fd(c, 2);
	return (ft_dprintf(2, "'\n"), 1);
}

char *get_word(char *str)
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

char *get_redir(t_cmd *cmd, char *str)
{
	char	c;
	int		i;

	(void)cmd;
	while (*str && ft_iswhitespace(*str))
		str++;
	if (!*str)
		return (ft_dprintf(2, "%s\n", ERR_NEWLINE), NULL);
	i = 0;
	if (*str == '|' || *str == '<' || *str == '>')
	{
		c = *str;
		while (*str++ == c)
			i++;
		return (error_syntax_too_much(i, c), NULL);
	}
	return (get_word(str));
}

int	is_redir(t_data *prompt, t_cmd *cmd, char *str, char c)
{
	int		i;
	char	*word;

	i = -1;
	while (str[++i] == c)
		str[i] = ' ';
	if (c == '<' && i == 3)
		return (ft_dprintf(2, "patate: we don't manage this option\n"), 1);
	if (c == '<' && i > 3)
		return (error_syntax_too_much(i - 3, c));
	if (c == '>' && i > 2)
		return (error_syntax_too_much(i - 2, c));
	if (!*(str + i))
		return(ft_dprintf(2, "%s", ERR_NEWLINE), 1);
	word = get_redir(cmd, str + i);
	if (c == '>' && i == 1)
	
	if (c == '>' && i == 2)
	
	if (c == '<' && i == 1)
	
	if (c == '<' && i == 2)
	
	printf("word :'%s'\n", word);
	free(word);
	return (0);
}
