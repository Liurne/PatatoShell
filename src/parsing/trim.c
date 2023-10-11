/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:41:32 by liurne            #+#    #+#             */
/*   Updated: 2023/10/10 18:20:00 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//virer tout les espaces en trop
//faire les expands
//faire le $?
//virer les quotes ferme


int	len_expand(char *str)
{
	int		len;
	char	*word;
	int		squote;
	int		dquote;
	
	len = 0;
	squote = 0;
	dquote = 0;
	while(*str && (!ft_iswhitespace(*str) || squote || dquote))
	{
		if (manage_quote(*str, &squote, &dquote))
			len--;
		len++;
		str++;
	}
	word = (char *)ft_calloc(len + 1, sizeof(char));
	if (!word)
		return(ft_dprintf(2, ERR_MALLOC), -1);
	
	return (len);
}
unsigned int true_len(char *line)
{
	unsigned int	len;
	int				squote;
	int				dquote;

	len =0;
	while(*line)
	{
		if (manage_quote(*line, &squote, &dquote))
		
		if (*line == '$' && !ft_iswhitespace(*(line + 1)) && !squote)
			len =
		
		line++;
	}
}
char *trim(char *line)
{
	char	*res;

	return (res);
}