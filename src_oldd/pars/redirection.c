/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:14:59 by liurne            #+#    #+#             */
/*   Updated: 2023/10/05 17:20:47 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.c"

int ft_isredir(t_data *prompt, t_cmd *cmd, char *str, char c)
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