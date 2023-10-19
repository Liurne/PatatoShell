/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liurne <liurne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:41:32 by liurne            #+#    #+#             */
/*   Updated: 2023/10/19 18:28:53 by liurne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//virer tout les espaces en trop
//faire les expands
//faire le $?
//virer les quotes ferme

static int	true_len(t_data *shell, char *cmd)
{
	int		len;
	t_quote	quote;

	len = 0;
	ft_bzero(&quote, sizeof(t_quote));
	while (*cmd && ft_iswhitespace(*cmd))
		cmd++;
	while (*cmd)
	{
		manage_quote(*cmd, &quote);
		if (*cmd == '$' && !quote.s)
			cmd += get_len_var(shell, cmd, &len);
		else
			cmd++;
		len++;
	}
	return (len);
}

char	*trim(t_data *shell, t_cmd *cmd, char *line)
{
	char	*res;
	t_quote	quote;
	int		i;
	int		j;

	ft_bzero(&quote, sizeof(t_quote));
	i = 0;
	j = 0;
	res = ft_calloc(true_len(shell, line) + 1, sizeof(char));
	if (!res)
		return (ft_dprintf(2, ERR_MALLOC), NULL);
	while (*line && ft_iswhitespace(*line))
		line++;
	while (line[i])
	{
		manage_quote(line[i], &quote);
		if (line[i] == '$' && !quote.s)
			line += put_var(shell, line + i, res, &j);
		else
			res[j] = line[i];
		j++;
		i++;
	}
	free(cmd->cmd);
	return (res);
}
