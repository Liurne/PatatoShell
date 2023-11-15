/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geteof.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:41:53 by jcoquard          #+#    #+#             */
/*   Updated: 2023/11/15 16:50:12 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*geteof(char *str, int *is_quote)
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
	}
	return (word);
}
