/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcoquard <jcoquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:45:02 by jcoquard          #+#    #+#             */
/*   Updated: 2023/10/27 19:06:21 by jcoquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	striswspace(char *str)
{
	while (*str)
	{
		if (!ft_iswhitespace(get_pos(*str)))
			return (0);
		str++;
	}
	return (1);
}

int	is_emptypipe(char *line)
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

int	error_syntax(char *str, char c)
{
	int	i;

	ft_dprintf(2, "patate: syntax error near unexpected token '");
	i = 0;
	while (str[i] && str[i] == c && (((c == '|' || c == '>') && i < 2)
			|| (c == '<' && i < 3)))
	{
		ft_putchar_fd(c, 2);
		i++;
	}
	ft_dprintf(2, "'\n");
	return (set_rval(2, NULL));
}

int	is_bracketvalid(char *str, char c, int *tmp)
{
	*tmp = 0;
	while (*str == c)
	{
		*tmp++;
		if ((c == '<' && *tmp > 3) || (c == '>' && *tmp > 2))
			return (error_syntax(str, c));
	}
	if (c == '<' && *tmp == 3)
		return (set_rval(2, ERR_OPTION));
	str += *tmp;
	while (*str && ft_iswhitespace(*str))
		str++;
	if (!*str)
		return (set_rval(2, ERR_NEWLINE));
	if (*str == '|' || *str == '<' || *str == '>')
		return (error_syntax(str, *str));
	return (0);
}
