/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:53:32 by liurne            #+#    #+#             */
/*   Updated: 2023/10/25 15:24:40 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_emptybpipe(char *line)
{
	while (*line && *line != '|')
	{
		if (!ft_iswhitespace(*line))
			return (0);
		line++;
	}
	if (*line == '|')
		return (1);
	return (0);
}

int	error_syntax_too_much(char *str, char c)
{
	ft_dprintf(2, "patate: syntax error near unexpected token '");
	if (c == '<')
		str += 3;
	if (c == '>')
		str += 2;
	while (*str && *str == c)
	{
		ft_putchar_fd(c, 2);
		str++;
	}
	return (ft_dprintf(2, "'\n"), 1);
}

int	is_bracketvalid(char *str, char c, int *tmp)
{
	int	i;

	*tmp = 0;
	while (str[*tmp] == c)
		*tmp += 1;
	if (c == '<' && *tmp == 3)
		return (ft_dprintf(2, ERR_MANAGE), 1);
	if ((c == '<' && *tmp > 3) || (c == '>' && *tmp > 2))
		return (error_syntax_too_much(str, c));
	str = str + *tmp;
	i = 0;
	while (*str && ft_iswhitespace(*str))
		str++;
	if (!*str)
		return (ft_dprintf(2, ERR_NEWLINE), g_rvalue = 2, 1);
	if (*str == '|' || *str == '<' || *str == '>')
	{
		c = *str;
		while (str[i] == c)
			i++;
		return (error_syntax_too_much(str, c), 1);
	}
	return (0);
}