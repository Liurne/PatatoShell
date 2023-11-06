/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:29:29 by jcoquard          #+#    #+#             */
/*   Updated: 2023/11/06 16:40:18 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pars_line(char *line)
{
	t_quote	quote;
	int		tmp;

	ft_bzero(&quote, sizeof(t_quote));
	while (*line && ft_iswhitespace(*line))
		line++;
	if (*line == '|')
		return (set_rval(2, ERR_PIPE));
	while (*line)
	{
		tmp = 1;
		manage_quote(*line, &quote);
		if (*line == '|' && !quote.s && !quote.d && is_emptypipe(line))
			return (set_rval(2, ERR_PIPE));
		if ((*line == '<' || *line == '>')
			&& is_bracketvalid(line, *line, &tmp) && !quote.s && !quote.d)
			return (2);
		line += tmp;
	}
	if (quote.s)
		return (set_rval(2, ERR_SQUOTE));
	if (quote.d)
		return (set_rval(2, ERR_DQUOTE));
	return (0);
}

int	manage_quote(char c, t_quote *quote)
{
	if (c == '\'' && !quote->d)
		quote->s = -(quote->s) + 1;
	if (c == '"' && !quote->s)
		quote->d = -(quote->d) + 1;
	if ((c == '\'' && !quote->d) || (c == '"' && !quote->s))
		return (1);
	return (0);
}

void	free_dtab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	get_pos(char c)
{
	if (c < 0)
		return (-c);
	return (c);
}

char	*ft_addchar(char *str, char c)
{
	int		len;
	char	*res;

	len = 0;
	if (str && *str)
		len = ft_strlen(str);
	res = ft_calloc(len + 2, sizeof(char));
	if (!res)
		return (set_rval(1, ERR_MALLOC), NULL);
	if (str && *str)
		ft_strlcpy(res, str, len + 1);
	res[len] = c;
	if (str && *str)
		free (str);
	return (res);
}
